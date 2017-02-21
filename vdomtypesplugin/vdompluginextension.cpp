#include "vdompluginextension.h"
#include "vdomtypeswidget.h"
#include <QtDesigner/QDesignerPropertySheetExtension>
#include <QVariant>
#include <QMetaProperty>

QMap<QString, QString> VdomPluginPropertySheetExtension::propertyGroups = VdomPluginPropertySheetExtension::makePropertyGroups();
QMap<QString, bool> VdomPluginPropertySheetExtension::invisibleProperties = VdomPluginPropertySheetExtension::makeInvisibleProperties();

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

QMap<QString, QString> VdomPluginPropertySheetExtension::makePropertyGroups()
{
    QMap<QString, QString> ret;
    // TODO: maybe assign better names
    ret["1"] = "Standard";
    ret["2"] = "Extended";
    ret["3"] = "Advanced";
    ret["4"] = "Specific";
    return ret;
}

QMap<QString, bool> VdomPluginPropertySheetExtension::makeInvisibleProperties()
{
    QMap<QString, bool> ret;
    ret["top"] = true;
    ret["left"] = true;
    ret["width"] = true;
    ret["height"] = true;
    return ret;
}

VdomPluginPropertySheetExtension::VdomPluginPropertySheetExtension(VdomTypesWidget *widget, QObject *parent) : QObject(parent)
{
    myWidget = widget;
    const QSharedPointer<VdomTypeInfo> &vdomType = myWidget->getVdomType();

    registerProperty("objectName");
    registerProperty("geometry");

    for (QMap<QString, AttributeInfo>::const_iterator i=vdomType->attributes.begin(); i!=vdomType->attributes.end(); i++) {
        registerProperty(i->attrName);
        const char* propName = i->attrName.toLatin1().constData();
        if (myWidget->property(propName).isValid())
            continue;
        myWidget->setProperty(propName, QVariant(QString("")));
    }
}

void VdomPluginPropertySheetExtension::registerProperty(const QString &name)
{
    Q_ASSERT(indexes.find(name) == indexes.end());
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

QString VdomPluginPropertySheetExtension::propertyGroup(int index) const
{
    QMap<QString, AttributeInfo>::iterator i = myWidget->getVdomType()->attributes.find(propertyName(index));
    if (i != myWidget->getVdomType()->attributes.end()) {
        QMap<QString, QString>::const_iterator j = propertyGroups.find(i->colorGroup);
        if (j != propertyGroups.end())
            return *j;
    }
    return "Standard";
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

bool VdomPluginPropertySheetExtension::isVisible(int index) const
{
    QString name = propertyName(index);
    if (invisibleProperties.find(name) != invisibleProperties.end())
        return false;
    QMap<QString, AttributeInfo>::iterator i = myWidget->getVdomType()->attributes.find(name);
    if (i != myWidget->getVdomType()->attributes.end() && !(i->visible))
        return false;
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
    const char *propName = name.toLatin1().data();
    QVariant value = myWidget->property(propName);
    if (value.isValid())
        return value;
    int realIndex = myWidget->metaObject()->indexOfProperty(propName);
    return myWidget->metaObject()->property(realIndex).read(myWidget);
}

void VdomPluginPropertySheetExtension::setProperty(int index, const QVariant &value)
{
    //qDebug(QString("setProperty %1 %2 %3\n").arg(index).arg(value.toString()).arg((int)value.type()).toLatin1().constData());
    QString name = propertyName(index);
    if (name.isEmpty())
        return;
    const char *propName = name.toLatin1().data();
    QVariant v = myWidget->property(propName);
    if (v.isValid()) {
        myWidget->setProperty(propName, value);
        return;
    }
    int realIndex = myWidget->metaObject()->indexOfProperty(propName);
    myWidget->metaObject()->property(realIndex).write(myWidget, value);
}

bool VdomPluginPropertySheetExtension::isChanged(int /*index*/) const
{
    return true;
}

void VdomPluginPropertySheetExtension::setChanged(int /*index*/, bool /*changed*/)
{
}
