#include "designercore.h"
#include "designercommon.h"
#include "integration/widgethost.h"

#include <QToolBar>

DesignerCore::DesignerCore(QWidget *parent, DesignerSignalHandler *handler,
                           const QString &widgetsFileName,
                           const QString &pluginPath) : signalHandler(handler)
{
    Q_ASSERT(parent);
    createDesignerCore(parent, widgetsFileName, pluginPath);
}

DesignerCore::~DesignerCore()
{
}

void DesignerCore::createDesignerCore(QWidget *parent, const QString &widgetsFileName,
                                      const QString &pluginPath)
{
    core = QDesignerComponents::createFormEditor(0);
    core->setTopLevel(parent);

    QDesignerComponents::createTaskMenu(core, 0);
    QDesignerComponents::initializeResources();
    initializeCorePlugins(pluginPath);
    QDesignerComponents::initializePlugins(core);

    formWindowManager = core->formWindowManager();

    core->setWidgetBox(QDesignerComponents::createWidgetBox(core, 0));
    core->setObjectInspector(QDesignerComponents::createObjectInspector(core, 0));
    core->setPropertyEditor(QDesignerComponents::createPropertyEditor(core, 0));
    core->setActionEditor(QDesignerComponents::createActionEditor(core, 0));

    signalSlotEditor = QDesignerComponents::createSignalSlotEditor(core, 0);
    resourceEditor = QDesignerComponents::createResourceEditor(core, 0);

    qdesigner_internal::QDesignerIntegration *integration = new qdesigner_internal::QDesignerIntegration(core, parent);
    core->setIntegration(integration);

    formWindow = formWindowManager->createFormWindow(0);

    widgetHost = new SharedTools::WidgetHost(0, formWindow);
    connect(widgetHost, SIGNAL(formWindowSizeChanged(int, int)), this, SLOT(formSizeChanged(int, int)));
    connect(formWindow, SIGNAL(widgetManaged(QWidget*)), this, SLOT(widgetManaged(QWidget*)));

    if (!widgetsFileName.isEmpty()) {
        QDesignerWidgetBoxInterface *wb = core->widgetBox();
        while (wb->categoryCount())
            wb->removeCategory(0);
        wb->setFileName(widgetsFileName);
        wb->load();
    }

    formWindowManager->setActiveFormWindow(formWindow);

    hidePropertyEditorButtons(core->propertyEditor());
}

void DesignerCore::initializeCorePlugins(const QString &pluginPath)
{
    if (!pluginPath.isEmpty())
        core->pluginManager()->setPluginPaths(QStringList(pluginPath));

    QList<QObject*> plugins = QPluginLoader::staticInstances();
    plugins += core->pluginManager()->instances();

    foreach (QObject *plugin, plugins) {
        if (QDesignerFormEditorPluginInterface *formEditorPlugin = qobject_cast<QDesignerFormEditorPluginInterface*>(plugin)) {
            if (!formEditorPlugin->isInitialized())
                formEditorPlugin->initialize(core);
        }
    }
}

void DesignerCore::widgetManaged(QWidget *widget)
{
    if (signalHandler)
        signalHandler->widgetManaged(widget);
}

void DesignerCore::formSizeChanged(int w, int h)
{
    if (const SharedTools::WidgetHost *wh = qobject_cast<const SharedTools::WidgetHost*>(sender())) {
        wh->formWindow()->setDirty(true);
        core->propertyEditor()->setPropertyValue(QLatin1String("geometry"), QRect(0, 0, w, h));
    }
}

QWidget* DesignerCore::getWidgetBox() const
{
    return core->widgetBox();
}

QWidget* DesignerCore::getForm() const
{
    return widgetHost;
}

QWidget* DesignerCore::getObjectInspector() const
{
    return core->objectInspector();
}

QWidget* DesignerCore::getPropertyEditor() const
{
    return core->propertyEditor();
}

void DesignerCore::setContent(const QString &content)
{
    formWindow->setContents(content);
    formWindow->setDirty(false);
}

QString DesignerCore::getContent() const
{
    return formWindow->contents();
}

void DesignerCore::hidePropertyEditorButtons(QObject *editor)
{
    QList<QToolBar*> toolbars = editor->findChildren<QToolBar*>();
    if (!toolbars.isEmpty()) {
        QList<QAction*> actions = toolbars.at(0)->actions();
        for (int i=1; i<actions.size(); i++)
            toolbars.at(0)->removeAction(actions.at(i));
    }
}
