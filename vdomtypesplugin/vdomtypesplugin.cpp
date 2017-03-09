#include "vdomtypesplugin.h"
#include "vdompluginextension.h"
#include "path.h"
#include "vdomclassfactory.h"
#include <QtPlugin>
#include <QtDesigner/QDesignerFormEditorInterface>
#include <QtDesigner/QExtensionManager>
#include <QtDesigner/QExtensionFactory>
#include <QtDesigner/QDesignerPropertySheetExtension>
#include <QXmlStreamWriter>
#include <QBuffer>

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
        if ((i->isTextField() || i->isMultiLine()) && !invisibleProperties.contains(i->attrName)) {
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

VdomTypesCollection::VdomTypesCollection(QObject *parent) : QObject(parent)
{
    QMap<QString, VdomTypeInfo> types = LoadTypes(defaultPath(defaultTypesFileName));

    qDebug("Loaded %d types", types.size());

    for (QMap<QString, VdomTypeInfo>::const_iterator i=types.begin(); i!=types.end(); i++) {
        if (i->container == "3")  // exclude top-level containers
            continue;
        VDOMWidget *w = createVdomWidget(i->typeName, NULL);
        if (w) {
            widgets.append(new VdomTypesPlugin(*i, *w, this));
            delete w;
        }
    }
}

QList<QDesignerCustomWidgetInterface*> VdomTypesCollection::customWidgets() const
{
    return widgets;
}

Q_EXPORT_PLUGIN2(customwidgetsplugin, VdomTypesCollection)
