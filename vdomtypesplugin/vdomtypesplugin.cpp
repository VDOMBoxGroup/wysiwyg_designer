#include "vdomtypesplugin.h"
#include "vdompluginextension.h"
#include "path.h"
#include "vdomclassfactory.h"
#include <QtPlugin>
#include <QtDesigner/QDesignerFormEditorInterface>
#include <QtDesigner/QExtensionManager>
#include <QtDesigner/QExtensionFactory>
#include <QtDesigner/QDesignerPropertySheetExtension>

VdomTypesPlugin::VdomTypesPlugin(const VdomTypeInfo &typeInfo, const VDOMWidget &widget, QObject *parent)
    : QObject(parent), initialized(false), vdomType(new VdomTypeInfo(typeInfo))
{
    className = widget.metaObject()->className();
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
    return QIcon();
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
    return (vdomType->container == "2" || vdomType->container == "3");
}

QString VdomTypesPlugin::domXml() const
{
    return QString("<ui language=\"c++\" displayname=\"%1\">\n"
                   " <widget class=\"%2\" name=\"%3\">\n"
                   "  <property name=\"geometry\">\n"
                   "   <rect>\n"
                   "    <x>0</x>\n"
                   "    <y>0</y>\n"
                   "    <width>100</width>\n"
                   "    <height>100</height>\n"
                   "   </rect>\n"
                   "  </property>\n"
                   "  <property name=\"toolTip\" >\n"
                   "   <string>%3</string>\n"
                   "  </property>\n"
                   "  <property name=\"whatsThis\" >\n"
                   "   <string>%3</string>\n"
                   "  </property>\n"
                   " </widget>\n"
                   "</ui>\n").arg(vdomType->displayName, className, vdomType->typeName);
}

QString VdomTypesPlugin::includeFile() const
{
    return "";
}

// ---

VdomTypesCollection::VdomTypesCollection(QObject *parent) : QObject(parent)
{
    QList<VdomTypeInfo> types = LoadTypes(defaultPath(defaultTypesFileName));

    qDebug("Loaded %d types", types.size());

    for (int i=0; i<types.size(); i++) {
        const VdomTypeInfo &typeInfo = types.at(i);
        if (typeInfo.container == "3")  // exclude top-level containers
            continue;
        VDOMWidget *w = createVdomWidget(typeInfo.typeName, NULL);
        if (w) {
            widgets.append(new VdomTypesPlugin(typeInfo, *w, this));
            delete w;
        }
    }
}

QList<QDesignerCustomWidgetInterface*> VdomTypesCollection::customWidgets() const
{
    return widgets;
}

Q_EXPORT_PLUGIN2(customwidgetsplugin, VdomTypesCollection)
