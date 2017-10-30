#include "designer.h"
#include "designercommon.h"
#include "designercore.h"

Designer::Designer() : core(NULL)
{
}

Designer::~Designer()
{
    delete core;
    core = NULL;
}

void Designer::initialize(QWidget *parent, DesignerSignalHandler *handler,
                          const QString &widgetsFileName, const QString &pluginPath)
{
    Q_ASSERT(!core);
    Q_ASSERT(parent);
    core = new DesignerCore(parent, handler, widgetsFileName, pluginPath);
    connect(core, SIGNAL(selectionChanged(QString, QString)), this, SIGNAL(selectionChanged(QString, QString)));
}

QWidget* Designer::widgetBox() const
{
    Q_ASSERT(core);
    return core->getWidgetBox();
}

QWidget* Designer::form() const
{
    Q_ASSERT(core);
    return core->getForm();
}

QWidget* Designer::objectInspector() const
{
    Q_ASSERT(core);
    return core->getObjectInspector();
}

QWidget* Designer::propertyEditor() const
{
    Q_ASSERT(core);
    return core->getPropertyEditor();
}

QString Designer::getSelectionName() const
{
    Q_ASSERT(core);
    return core->getSelectionName();
}

QString Designer::getSelectionType() const
{
    Q_ASSERT(core);
    return core->getSelectionType();
}

QMap<QString, QString> Designer::getObjects() const
{
    Q_ASSERT(core);
    return core->getObjects();
}

void Designer::setContent(const QString &content)
{
    Q_ASSERT(core);
    core->setContent(content);
}

QString Designer::getContent() const
{
    Q_ASSERT(core);
    return core->getContent();
}
