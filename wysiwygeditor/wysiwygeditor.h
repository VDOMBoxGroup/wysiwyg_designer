#ifndef WYSIWYGEDITOR_H
#define WYSIWYGEDITOR_H

#include <QVariant>
#include <QStringList>
#include <QMap>
#include <QByteArray>
#include "designer.h"

class QWidget;
class LocalSocketClient;
class VdomXmlItem;

class VApplicationService;
class VRestReply;

class WysiwygEditor: public QObject, public DesignerSignalHandler
{
    Q_OBJECT
public:
    WysiwygEditor(const QString &server, const QString &app);
    virtual ~WysiwygEditor();

    Q_INVOKABLE void initialize(QWidget *parent,
                                const QString &widgetsFileName = QString(),
                                const QString &pluginPath = QString(),
                                const QString &resourcePath = QString());

    Q_INVOKABLE bool setContent(const QString &content = QString());
    Q_INVOKABLE QString getContent() const;
    Q_INVOKABLE QString getContent(QStringList &resources) const;
    Q_INVOKABLE QString getContent(QStringList &resources, QStringList &errors) const;
    Q_INVOKABLE void saveResources() const;

    Q_INVOKABLE QWidget* widgetBox() const;
    Q_INVOKABLE QWidget* form() const;
    Q_INVOKABLE QWidget* objectInspector() const;
    Q_INVOKABLE QWidget* propertyEditor() const;

    Q_INVOKABLE QString getSelectionName() const;
    Q_INVOKABLE QString getSelectionType() const;
    Q_INVOKABLE QMap<QString, QStringList> getE2vdomEvents(const QString &typeName) const;
    Q_INVOKABLE QMap<QString, QStringList> getE2vdomActions(const QString &typeName) const;
    Q_INVOKABLE QMap<QString, QString> getObjects() const;

Q_SIGNALS:
    void modelChanged() const;
    void attributeChanged(const QObject &object, const QString &name, const QVariant &value) const;
    void widgetCreated(const QWidget &widget) const;
    void widgetDeleted(const QWidget &widget) const;
    void selectionChanged(const QString &newSelection, const QString &oldSelection) const;

private:
    void widgetManaged(QWidget*);
    void widgetRemoved(QWidget*);
    void changed();
    void propertyChanged(const QObject &object, const QString &name, const QVariant &value);

private:
    QString getResourcePath(const QString &id) const;
    void sendWysiwygData(const QString &wysiwyg) const;
    void sendResources(const QMap<QString, QByteArray> &res) const;
    void sendResource(const QString &id, const QByteArray &content) const;
    void queryWysiwyg(const QString &vdomxml);
    void queryResources(const QStringList &res) const;
    void processResourcesReply(const QString &r) const;
    void processSaveResourcesReply(const QString &r);
    QString makeSaveResRequest() const;
    void sendUpdate() const;
    void sendErrorObjects() const;

private slots:
    void onClientConnect();
    void onWysiwygReply(VRestReply*);
    void onResourcesReply(VRestReply*);
    void onSaveResourcesReply(VRestReply*);

private:
    Designer *designer;
    LocalSocketClient *client;
    QString vdomxmlstr;
    VdomXmlItem *vdomxml;
    QStringList resources;
    QStringList errors;
    QStringList errorObjects;
    QString resPath;
    QString serverAddr;
    QString appId;
    const VApplicationService *service;
    int requestId;
    int responseId;

    Q_DISABLE_COPY(WysiwygEditor)
};

#endif // WYSIWYGEDITOR_H
