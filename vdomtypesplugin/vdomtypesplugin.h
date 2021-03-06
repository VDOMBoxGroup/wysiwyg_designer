#ifndef VDOMTYPESPLUGIN_H
#define VDOMTYPESPLUGIN_H

#include <QDesignerCustomWidgetInterface>
#include <QString>
#include <QSharedPointer>
#include "vdomtypesplugin_global.h"
#include "typesloader.h"
#include "listener.h"

class VDOMWidget;

class VdomTypesPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    VdomTypesPlugin(const VdomTypeInfo &typeInfo, const VDOMWidget &widget, QObject *parent = 0);

    bool isContainer() const;
    bool isInitialized() const;
    QIcon icon() const;
    QString domXml() const;
    QString group() const;
    QString includeFile() const;
    QString name() const;
    QString toolTip() const;
    QString whatsThis() const;
    QWidget *createWidget(QWidget *parent);
    void initialize(QDesignerFormEditorInterface *core);

    static void setCore(QDesignerFormEditorInterface *d) { if (!core) core = d; }
    static QDesignerFormEditorInterface* getCore() { return core; }

private:
    bool initialized;
    QSharedPointer<VdomTypeInfo> vdomType;
    QString className;

    static QDesignerFormEditorInterface *core;
};

class VdomTypesCollection: public QObject, public QDesignerCustomWidgetCollectionInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)

public:
    VdomTypesCollection(QObject *parent = 0);

    virtual QList<QDesignerCustomWidgetInterface*> customWidgets() const;

private slots:
    void onWysiwyg(const QString &wysiwyg);

private:
    QList<QDesignerCustomWidgetInterface*> widgets;
    Listener listener;
};

#endif // VDOMTYPESPLUGIN_H
