#include "wysiwygeditor.h"
#include "widgetsfile.h"
#include "path.h"
#include "converter.h"
#include "util.h"
#include "localsocketclient.h"
#include "vdomxml.h"
#include "VdomCore/vapplicationservice.h"
#include "VdomCore/vrestreply.h"
#include <QUuid>
#include <QFile>
#include <QFileInfo>
#include <QRegExp>
#include <QXmlStreamReader>

#define OBJ_ID "API"
#define WYSIWYG_ACTION "wysiwyg"
#define RES_ACTION "get_resources"

#define RESOURCE "resource"

static QRegExp resRegExp("#Res\\(([^\\)]+)\\)");

static const QString defaultContent = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
"<ui version=\"4.0\">"
" <class>Container</class>"
" <widget class=\"Container\" name=\"container\">"
"  <property name=\"geometry\">"
"   <rect>"
"    <x>0</x>"
"    <y>0</y>"
"    <width>580</width>"
"    <height>390</height>"
"   </rect>"
"  </property>"
" </widget>"
" <resources/>"
" <connections/>"
"</ui>";

WysiwygEditor::WysiwygEditor(const QString &server, const QString &app) : designer(NULL), client(NULL)
{
    vdomxml = new VdomXmlItem();
    service = new VApplicationService();
    serverAddr = server;
    appId = app;
}

WysiwygEditor::~WysiwygEditor()
{
    delete designer;
    designer = NULL;
    delete vdomxml;
    delete service;
}

void WysiwygEditor::initialize(QWidget *parent, const QString &widgetsFileName,
                               const QString &pluginPath, const QString &resourcePath)
{
    Q_ASSERT(!designer);
    Q_ASSERT(!client);
    Q_ASSERT(parent);

    MakeTempPath();

    QString widgetsFile = widgetsFileName.isEmpty() ? DefaultWidgetsFilePath() : widgetsFileName;
    WriteWidgetsFile(widgetsFile, CreateWidgetsXml());

    designer = new Designer();
    designer->initialize(parent, this, widgetsFile,
                         pluginPath.isEmpty() ? DefaultPath(defaultPluginPath) : pluginPath);

    // load vdom types for converter
    GetVdomTypes();

    resPath = resourcePath.isEmpty() ? DefaultResourcePath() : resourcePath;

    client = new LocalSocketClient(this);
    connect(client, SIGNAL(connected()), this, SLOT(onClientConnect()));
}

QWidget* WysiwygEditor::widgetBox() const
{
    Q_ASSERT(designer);
    return designer->widgetBox();
}

QWidget* WysiwygEditor::form() const
{
    Q_ASSERT(designer);
    return designer->form();
}

QWidget* WysiwygEditor::objectInspector() const
{
    Q_ASSERT(designer);
    return designer->objectInspector();
}

QWidget* WysiwygEditor::propertyEditor() const
{
    Q_ASSERT(designer);
    return designer->propertyEditor();
}

void WysiwygEditor::setContent(const QString &content)
{
    Q_ASSERT(designer);
    if (!content.isEmpty()) {
        designer->setContent(VdomxmlToQml(content));
        //qDebug(vdomxmlToQml(content).toLatin1().constData());
    } else {
        designer->setContent(defaultContent);
    }
}

QString WysiwygEditor::getContent(QStringList &res) const
{
    QStringList e;
    return getContent(res, e);
}

QString WysiwygEditor::getContent(QStringList &res, QStringList &err) const
{
    res = resources;
    err = errors;
    return vdomxmlstr;
    //return designer->getContent();
}

void WysiwygEditor::widgetManaged(QWidget *w)
{
    emit widgetCreated(*w);
}

void WysiwygEditor::widgetRemoved(QWidget *w)
{
    emit widgetDeleted(*w);
}

void WysiwygEditor::changed()
{
    resources.clear();
    errors.clear();
    QString newVdomxmlStr = QmlToVdomxml(designer->getContent(), resources, errors);
    VdomXmlItem newVdomXml = ParseVdomxml(newVdomxmlStr);
    if (*vdomxml != newVdomXml) {
        const VdomXmlItem *d = newVdomXml.firstDiff(*vdomxml);
        if (d) {
//            qDebug("==================");
//            qDebug("Old: %s", vdomxmlstr.toLatin1().constData());
//            qDebug("New: %s", newVdomxmlStr.toLatin1().constData());
//            qDebug("Diff: %s", d->getVdomxml(true).toLatin1().constData());
//            qDebug("\n");
            //qDebug(d->getVdomxml().toLatin1().constData());
            queryWysiwyg(d->getVdomxml(true));
        }
    }
    vdomxmlstr = newVdomxmlStr;
    *vdomxml = newVdomXml;
    emit modelChanged();
}

void WysiwygEditor::propertyChanged(const QObject &object, const QString &name, const QVariant &value)
{
    emit attributeChanged(object, name, value);
}

void WysiwygEditor::sendResources(const QMap<QString, QByteArray> &res) const
{
    for (QMap<QString, QByteArray>::const_iterator i=res.begin(); i!=res.end(); i++)
        sendResource(i.key(), i.value());
}

void WysiwygEditor::sendResource(const QString &id, const QByteArray &content) const
{
    Q_ASSERT(client);
    QString path = getResourcePath(id);
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug("Can't open file \'%s\': %s", path.toLatin1().constData(), file.errorString().toLatin1().constData());
        return;
    }
    file.write(content);
    client->send("update");
}

QString WysiwygEditor::getResourcePath(const QString &id) const
{
    return resPath + "/" + id;
}

void WysiwygEditor::sendWysiwygData(const QString &wysiwyg) const
{
    Q_ASSERT(client);
    QStringList newRes;
    QString result = wysiwyg;
    int start = 0;
    while ((start = resRegExp.indexIn(result, start)) != -1) {
        int length = resRegExp.matchedLength();
        QString id = resRegExp.cap(1);
        QString path = getResourcePath(id);
        if (QFileInfo(id).exists())
            path = id;
        else if (!QFileInfo(path).exists())
            newRes.append(id);
        result.replace(start, length, path);
        start += id.length();
    }
    if (!newRes.isEmpty()) {
        qDebug("Need resources: %s", newRes.join(",").toLatin1().constData());
        queryResources(newRes);
    }
    qDebug("Sending: %s", result.toLatin1().constData());
    client->send(result);
}

void WysiwygEditor::onClientConnect()
{
    // display wysiwyg of initial form
    QStringList r, e;
    queryWysiwyg(getContent(r, e));
}

void WysiwygEditor::queryWysiwyg(const QString &vdomxml) const
{
    VRestReply *r = service->restApiCall2(serverAddr, appId, OBJ_ID, WYSIWYG_ACTION, vdomxml);
    connect(r, SIGNAL(finished(VRestReply*)), this, SLOT(onWysiwygReply(VRestReply*)));
}

void WysiwygEditor::onWysiwygReply(VRestReply *r)
{
    if (r->isSuccess()) {
        QString wysiwyg = r->getResponseText();
        qDebug(QString("Got: %1").arg(wysiwyg).toLatin1().constData());
        sendWysiwygData(wysiwyg);
    }
    disconnect(r, SIGNAL(finished(VRestReply*)), this, SLOT(onWysiwygReply(VRestReply*)));
    r->deleteLater();
}

void WysiwygEditor::queryResources(const QStringList &res) const
{
    VRestReply *r = service->restApiCall2(serverAddr, appId, OBJ_ID, RES_ACTION, res.join(","));
    connect(r, SIGNAL(finished(VRestReply*)), this, SLOT(onResourcesReply(VRestReply*)));
}

void WysiwygEditor::onResourcesReply(VRestReply *r)
{
    if (r->isSuccess()) {
        QString res = r->getResponseText();
        //qDebug(QString("Res: %1").arg(res).toLatin1().constData());
        processResourcesReply(res);
    }
    disconnect(r, SIGNAL(finished(VRestReply*)), this, SLOT(onResourcesReply(VRestReply*)));
    r->deleteLater();
}

void WysiwygEditor::processResourcesReply(const QString &r) const
{
    QXmlStreamReader xml(r);

    while (!xml.atEnd()) {
        xml.readNextStartElement();
        if (xml.tokenType() == QXmlStreamReader::StartElement && equals(xml, RESOURCE)) {
            QString id = attr(xml, "id");
            QByteArray content = QByteArray::fromBase64(get(xml).toLatin1());
            if (!id.isEmpty() && !content.isEmpty()) {
                qDebug(QString("Send res %1").arg(id).toLatin1().constData());
                sendResource(id, content);
            }
        }
    }
}
