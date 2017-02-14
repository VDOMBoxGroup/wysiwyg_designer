#ifndef VDOMTYPESPLUGIN_H
#define VDOMTYPESPLUGIN_H

#include "vdomtypesplugin_global.h"
#include <QDesignerCustomWidgetInterface>

class VdomTypesPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    VdomTypesPlugin(QObject *parent = 0);

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

private:
    bool initialized;
};

#endif // VDOMTYPESPLUGIN_H
