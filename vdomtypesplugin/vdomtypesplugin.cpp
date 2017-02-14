#include "vdomtypesplugin.h"
#include "vdomtypeswidget.h"
#include "vdompluginextension.h"
#include <QtPlugin>
#include <QtDesigner/QDesignerFormEditorInterface>
#include <QtDesigner/QExtensionManager>
#include <QtDesigner/QExtensionFactory>
#include <QtDesigner/QDesignerPropertySheetExtension>

VdomTypesPlugin::VdomTypesPlugin(QObject *parent)
    : QObject(parent)
{
    initialized = false;
}

void VdomTypesPlugin::initialize(QDesignerFormEditorInterface *core)
{
    if (initialized)
        return;

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
    QWidget *widget = new VdomTypesWidget(parent);
    return widget;
}

QString VdomTypesPlugin::name() const
{
    return "VdomTypesWidget";
}

QString VdomTypesPlugin::group() const
{
    return "VDOM Types";
}

QIcon VdomTypesPlugin::icon() const
{
    return QIcon();
}

QString VdomTypesPlugin::toolTip() const
{
    return "test tooltip";
}

QString VdomTypesPlugin::whatsThis() const
{
    return "test whatsthis";
}

bool VdomTypesPlugin::isContainer() const
{
    return false;
}

QString VdomTypesPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"VdomTypesWidget\" name=\"test\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>100</width>\n"
           "    <height>100</height>\n"
           "   </rect>\n"
           "  </property>\n"
           "  <property name=\"toolTip\" >\n"
           "   <string>123</string>\n"
           "  </property>\n"
           "  <property name=\"whatsThis\" >\n"
           "   <string>456</string>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>\n";
}

QString VdomTypesPlugin::includeFile() const
{
    return "";
}

Q_EXPORT_PLUGIN2(customwidgetplugin, VdomTypesPlugin)
