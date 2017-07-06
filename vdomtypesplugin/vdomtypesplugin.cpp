#include "vdomtypesplugin.h"
#include "vdompluginextension.h"
#include "path.h"
#include "util.h"
#include "vdomclassfactory.h"
#include "protocol.h"
#include "wysiwyg.h"
#include <QtPlugin>
#include <QtDesigner/QDesignerFormEditorInterface>
#include <QtDesigner/QDesignerFormWindowManagerInterface>
#include <QtDesigner/QExtensionManager>
#include <QtDesigner/QExtensionFactory>
#include <QtDesigner/QDesignerPropertySheetExtension>
#include <QtDesigner/QDesignerPropertyEditorInterface>
#include <QXmlStreamWriter>
#include <QBuffer>

QDesignerFormEditorInterface *VdomTypesPlugin::core = NULL;

VdomTypesPlugin::VdomTypesPlugin(const VdomTypeInfo &typeInfo, const VDOMWidget &widget, QObject *parent)
    : QObject(parent), initialized(false), vdomType(new VdomTypeInfo(typeInfo))
{
    className = widget.metaObject()->className();
}

void VdomTypesPlugin::initialize(QDesignerFormEditorInterface *core)
{
    if (initialized)
        return;

    setCore(core);

    QExtensionManager *manager = core->extensionManager();
    QExtensionFactory *factory = new VdomPluginExtensionFactory(manager);

    Q_ASSERT(manager);
    manager->registerExtensions(factory, Q_TYPEID(QDesignerPropertySheetExtension));

    initialized = true;
}

bool VdomTypesPlugin::isInitialized() const
{
    return initialized;
}

QWidget *VdomTypesPlugin::createWidget(QWidget *parent)
{
    VDOMWidget *w = createVdomWidget(vdomType->typeName, parent);
    w->setVdomType(vdomType);
    return w;
}

QString VdomTypesPlugin::name() const
{
    return className;
}

QString VdomTypesPlugin::group() const
{
    return vdomType->category;
}

QIcon VdomTypesPlugin::icon() const
{
    return vdomType->icon;
}

QString VdomTypesPlugin::toolTip() const
{
    return vdomType->typeName;
}

QString VdomTypesPlugin::whatsThis() const
{
    return vdomType->typeName;
}

bool VdomTypesPlugin::isContainer() const
{
    return vdomType->isContainer();
}

void writeGeometry(QXmlStreamWriter &xml)
{
    xml.writeStartElement("property");
    xml.writeAttribute("name", "geometry");
    xml.writeStartElement("rect");
    xml.writeTextElement("x", "0");
    xml.writeTextElement("y", "0");
    xml.writeTextElement("width", "100");
    xml.writeTextElement("height", "100");
    xml.writeEndElement();
    xml.writeEndElement();
}

void writeStringProperty(QXmlStreamWriter &xml, const QString &name, const QString &value)
{
    xml.writeStartElement("property");
    xml.writeAttribute("name", name);
    xml.writeTextElement("string", value);
    xml.writeEndElement();
}

QString VdomTypesPlugin::domXml() const
{
    QBuffer buffer;
    buffer.open(QBuffer::WriteOnly);

    QXmlStreamWriter xml(&buffer);
    xml.setAutoFormatting(true);

    xml.writeStartElement("ui");
    xml.writeAttribute("language", "c++");
    xml.writeAttribute("displayname", vdomType->displayName);

    xml.writeStartElement("widget");
    xml.writeAttribute("class", className);
    xml.writeAttribute("name", vdomType->typeName);
    writeGeometry(xml);
    writeStringProperty(xml, "toolTip", vdomType->typeName);
    writeStringProperty(xml, "whatsThis", vdomType->typeName);
    for (QMap<QString, AttributeInfo>::const_iterator i=vdomType->attributes.begin(); i!=vdomType->attributes.end(); i++)
        if ((i->isTextField() || i->isMultiLine()) && !invisibleProperties.contains(i->attrName))
            writeStringProperty(xml, i->attrName, i->defaultValueStr);
    xml.writeEndElement(); // widget

    xml.writeStartElement("customwidgets");
    xml.writeStartElement("customwidget");
    xml.writeTextElement("class", className);
    xml.writeStartElement("propertyspecifications");
    for (QMap<QString, AttributeInfo>::const_iterator i=vdomType->attributes.begin(); i!=vdomType->attributes.end(); i++)
        if ((i->isTextField() || i->isMultiLine() || i->isPageLink() || i->isObjectList() || i->isExternalEditor()) && !invisibleProperties.contains(i->attrName)) {
            xml.writeStartElement("stringpropertyspecification");
            xml.writeAttribute("name", i->attrName);
            xml.writeAttribute("notr", "true");
            xml.writeAttribute("type", "multiline");
            xml.writeEndElement(); // stringpropertyspecification
        }
    xml.writeEndElement(); // propertyspecifications
    xml.writeEndElement(); // customwidget
    xml.writeEndElement(); // customwidgets

    xml.writeEndElement(); // ui

    return buffer.buffer();
}

QString VdomTypesPlugin::includeFile() const
{
    return "";
}

// ---

QObject* FindWidget(QObject *parent, const QString &name)
{
//    qDebug("\n---");
//    qDebug("Find %s (%s)", name.toLatin1().constData(), parent->objectName().toLatin1().constData());
    if (!parent)
        return NULL;
    if (name == parent->objectName())
        return parent;
    QObjectList children = parent->children();
//    qDebug("Find 1: %d", children.size());
    for (QObjectList::const_iterator i=children.begin(); i!=children.end(); i++) {
//        qDebug("%s", (*i)->objectName().toLatin1().constData());
        if (name == (*i)->objectName()) {
//            qDebug("Found");
            return *i;
        }
    }
//    qDebug("Find 2");
    for (QObjectList::const_iterator i=children.begin(); i!=children.end(); i++) {
        QObject *obj = FindWidget(*i, name);
        if (obj)
            return obj;
    }
//    qDebug("Find 3");
    return NULL;
}

VdomTypesCollection::VdomTypesCollection(QObject *parent) : QObject(parent)
{
    QMap<QString, VdomTypeInfo> types = LoadTypes(DefaultPath(defaultTypesFileName));

    qDebug("Loaded %d types", types.size());

    for (QMap<QString, VdomTypeInfo>::const_iterator i=types.begin(); i!=types.end(); i++) {
        if (i->isTopContainer())
            continue;
        VDOMWidget *w = createVdomWidget(i->typeName, NULL);
        if (w) {
            widgets.append(new VdomTypesPlugin(*i, *w, this));
            delete w;
        }
    }

    connect(&listener, SIGNAL(receivedWysiwyg(const QString&)), this, SLOT(onWysiwyg(const QString&)));
}

QList<QDesignerCustomWidgetInterface*> VdomTypesCollection::customWidgets() const
{
    return widgets;
}

bool WidgetZindexCompare(VdomTypesWidget *w1, VdomTypesWidget *w2)
{
    return w1->zindex() < w2->zindex();
}

void SortTypesWidgets(VdomTypesWidget *top)
{
    QList<VdomTypesWidget*> ch = top->findChildren<VdomTypesWidget*>();
    qSort(ch.begin(), ch.end(), WidgetZindexCompare);
    top->raise();
    for (QList<VdomTypesWidget*>::iterator i=ch.begin(); i!=ch.end(); i++)
        (*i)->raise();
}

void UpdateTypesWidgets(VdomTypesWidget *top)
{
    top->updateWysiwyg();
    QList<VdomTypesWidget*> ch = top->findChildren<VdomTypesWidget*>();
    for (QList<VdomTypesWidget*>::iterator i=ch.begin(); i!=ch.end(); i++)
        (*i)->updateWysiwyg();
}

// workaround Designer issue with loost focus
void UpdateSelection(QDesignerFormEditorInterface *core)
{
    QWidget *current = qobject_cast<QWidget*>(core->propertyEditor()->object());
    if (current) {
        core->formWindowManager()->activeFormWindow()->clearSelection();
        core->formWindowManager()->activeFormWindow()->selectWidget(current);
    }
}

void VdomTypesCollection::onWysiwyg(const QString &wysiwyg)
{
    QDesignerFormEditorInterface *core = VdomTypesPlugin::getCore();
    if (!core) {
        qDebug("Designer core is not available");
        return;
    }

    if (wysiwyg == "update") {
        VdomTypesWidget *top = qobject_cast<VdomTypesWidget*>(core->formWindowManager()->activeFormWindow()->mainContainer());
        if (top) {
            UpdateTypesWidgets(top);
            SortTypesWidgets(top);
        }
        UpdateSelection(core);
        return;
    } else if (wysiwyg.startsWith("error")) {
        QObject *obj = FindWidget(core->formWindowManager()->activeFormWindow()->mainContainer(), wysiwyg.split(" ").last());
        if (obj) {
            VdomTypesWidget *tw = qobject_cast<VdomTypesWidget*>(obj);
            if (tw) tw->setError();
        }
        return;
    }

    bool changed = false;
    QList<WItem> w = ParseWysiwyg(wysiwyg);
    for (QList<WItem>::const_iterator i=w.begin(); i!=w.end(); i++) {
//        qDebug("Plugin: wysiwyg \'%s\'", i->objectName().toLatin1().constData());
        QObject *obj = FindWidget(core->formWindowManager()->activeFormWindow()->mainContainer(), i->objectName());
        if (obj) {
            VdomTypesWidget *tw = qobject_cast<VdomTypesWidget*>(obj);
            if (tw && !i->isEmpty()) {
                tw->setWysiwyg(*i);
                changed = true;
            }
        }
    }

    if (changed) {
        VdomTypesWidget *top = qobject_cast<VdomTypesWidget*>(core->formWindowManager()->activeFormWindow()->mainContainer());
        if (top) {
            //qDebug("changed");
            top->updateZindex();
            SortTypesWidgets(top);
        }
        UpdateSelection(core);
    }
}

Q_EXPORT_PLUGIN2(customwidgetsplugin, VdomTypesCollection)
