#include "vdompluginextension.h"
#include "vdomtypeswidget.h"
#include "util.h"
#include <QtDesigner/QDesignerPropertySheetExtension>
#include <QVariant>
#include <QMetaProperty>

QMap<QString, QString> makePropertyGroups()
{
    QMap<QString, QString> ret;
    // TODO: maybe assign better names
    ret["1"] = "Standard";
    ret["2"] = "Extended";
    ret["3"] = "Advanced";
    ret["4"] = "Specific";
    return ret;
}

QSet<QString> makeInvisibleProperties()
{
    QSet<QString> ret;
    ret.insert("top");
    ret.insert("left");
    ret.insert("width");
    ret.insert("height");
    return ret;
}

QMap<QString, QString> propertyGroups = makePropertyGroups();
QSet<QString> invisibleProperties = makeInvisibleProperties();

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
    for (QMap<QString, QString>::const_iterator i=propertyGroups.begin(); i!=propertyGroups.end(); i++)
        registerProperties(i.key());
}

void VdomPluginPropertySheetExtension::registerProperties(const QString &groupName)
{
    const QSharedPointer<VdomTypeInfo> &vdomType = myWidget->getVdomType();
    for (QMap<QString, AttributeInfo>::const_iterator i=vdomType->attributes.begin(); i!=vdomType->attributes.end(); i++) {
        if (i->colorGroup != groupName)
            continue;
        QString attrName = TranslateAttributeVdomToQml(vdomType->typeName, i->attrName);
        registerProperty(attrName);
        const char* propName = attrName.toLatin1().constData();
        if (!myWidget->property(propName).isValid())
            myWidget->setProperty(propName, i->defaultValue);
    }
}

void VdomPluginPropertySheetExtension::registerProperty(const QString &name)
{
    Q_ASSERT(!indexes.contains(name));
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
    const QSharedPointer<VdomTypeInfo> &vdomType = myWidget->getVdomType();
    QMap<QString, AttributeInfo>::const_iterator i = vdomType->findAttribute(propertyName(index));
    if (i != vdomType->attributes.end()) {
        QMap<QString, QString>::const_iterator j = propertyGroups.find(i->colorGroup);
        if (j != propertyGroups.end())
            return *j;
    }
    return propertyGroups["1"];
}

void VdomPluginPropertySheetExtension::setPropertyGroup(int /*index*/, const QString &/*group*/)
{
}

bool VdomPluginPropertySheetExtension::hasReset(int index) const
{
    const QSharedPointer<VdomTypeInfo> &vdomType = myWidget->getVdomType();
    return vdomType->hasAttribute(propertyName(index));
}

bool VdomPluginPropertySheetExtension::reset(int index)
{
    const QSharedPointer<VdomTypeInfo> &vdomType = myWidget->getVdomType();
    QMap<QString, AttributeInfo>::const_iterator attr = vdomType->findAttribute(propertyName(index));
    if (attr != vdomType->attributes.end()) {
        setProperty(index, attr->defaultValue);
        return true;
    }
    return false;
}

bool VdomPluginPropertySheetExtension::isVisible(int index) const
{
    QString name = propertyName(index);
    if (invisibleProperties.contains(name))
        return false;
    const QSharedPointer<VdomTypeInfo> &vdomType = myWidget->getVdomType();
    QMap<QString, AttributeInfo>::const_iterator i = vdomType->findAttribute(name);
    if (i != vdomType->attributes.end() && !(i->visible))
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
    QString name = propertyName(index);
    if (name.isEmpty())
        return;

    const QSharedPointer<VdomTypeInfo> &vdomType = myWidget->getVdomType();
    QMap<QString, AttributeInfo>::const_iterator attr = vdomType->findAttribute(name);

    const char *propName = name.toLatin1().data();
    QVariant v = myWidget->property(propName);
    if (v.isValid()) {
        if (attr != vdomType->attributes.end() && attr->isDropDown())
            myWidget->setProperty(propName, attr->getDropDownValue(value));
        else
            myWidget->setProperty(propName, value);
        return;
    }
    int realIndex = myWidget->metaObject()->indexOfProperty(propName);
    myWidget->metaObject()->property(realIndex).write(myWidget, value);
}

bool VdomPluginPropertySheetExtension::isChanged(int index) const
{
    const QSharedPointer<VdomTypeInfo> &vdomType = myWidget->getVdomType();
    QVariant value = property(index);
    QMap<QString, AttributeInfo>::const_iterator attr = vdomType->findAttribute(propertyName(index));
    if (attr != vdomType->attributes.end() && attr->equalsToDefault(value))
        return false;
    return true;
}

void VdomPluginPropertySheetExtension::setChanged(int /*index*/, bool /*changed*/)
{
}
