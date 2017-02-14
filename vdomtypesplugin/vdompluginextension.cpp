#include "vdompluginextension.h"
#include "vdomtypeswidget.h"
#include <QtDesigner/QDesignerPropertySheetExtension>
#include <QVariant>
#include <QMetaProperty>

VdomPluginExtensionFactory::VdomPluginExtensionFactory(QExtensionManager *parent): QExtensionFactory(parent)
{
}

QObject* VdomPluginExtensionFactory::createExtension(QObject *object, const QString &iid, QObject *parent) const
{
    VdomTypesWidget *widget = qobject_cast<VdomTypesWidget*>(object);

    if (widget && (iid == Q_TYPEID(QDesignerPropertySheetExtension))) {
        return new VdomPluginPropertySheetExtension(widget, parent);
    } else {
        return 0;
    }
}

VdomPluginPropertySheetExtension::VdomPluginPropertySheetExtension(VdomTypesWidget *widget, QObject *parent) : QObject(parent)
{
    myWidget = widget;

    registerProperty("objectName");
    registerProperty("geometry");
}

void VdomPluginPropertySheetExtension::registerProperty(const QString &name)
{
    int index = indexes.count();
    indexes[name] = index;
    names[index] = name;
}

int VdomPluginPropertySheetExtension::count() const
{
    return indexes.count();
}

int VdomPluginPropertySheetExtension::indexOf(const QString &name) const
{
    QMap<QString, int>::const_iterator i = indexes.find(name);
    if (i != indexes.end()) return i.value();
    else return -1;
}

QString VdomPluginPropertySheetExtension::propertyName(int index) const
{
    QMap<int, QString>::const_iterator i = names.find(index);
    if (i != names.end()) return i.value();
    else return "";
}

QString VdomPluginPropertySheetExtension::propertyGroup(int /*index*/) const
{
    return "standard";
}

void VdomPluginPropertySheetExtension::setPropertyGroup(int /*index*/, const QString &/*group*/)
{
}

bool VdomPluginPropertySheetExtension::hasReset(int /*index*/) const
{
    return false;
}

bool VdomPluginPropertySheetExtension::reset(int /*index*/)
{
    return false;
}

bool VdomPluginPropertySheetExtension::isVisible(int /*index*/) const
{
    return true;
}

void VdomPluginPropertySheetExtension::setVisible(int /*index*/, bool /*b*/)
{
}

bool VdomPluginPropertySheetExtension::isAttribute(int /*index*/) const
{
    return false;
}

void VdomPluginPropertySheetExtension::setAttribute(int /*index*/, bool /*b*/)
{
}

QVariant VdomPluginPropertySheetExtension::property(int index) const
{
    QString name = propertyName(index);
    int realIndex = myWidget->metaObject()->indexOfProperty(name.toLatin1().data());
    return myWidget->metaObject()->property(realIndex).read(myWidget);
}

void VdomPluginPropertySheetExtension::setProperty(int index, const QVariant &value)
{
    QString name = propertyName(index);
    if (name.isEmpty())
        return;
    int realIndex = myWidget->metaObject()->indexOfProperty(name.toLatin1().data());
    myWidget->metaObject()->property(realIndex).write(myWidget, value);
}

bool VdomPluginPropertySheetExtension::isChanged(int /*index*/) const
{
    return true;
}

void VdomPluginPropertySheetExtension::setChanged(int /*index*/, bool /*changed*/)
{
}
