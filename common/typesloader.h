#ifndef TYPESLOADER_H
#define TYPESLOADER_H

#include <QStringList>
#include <QMap>
#include <QVariant>
#include <QIcon>

class AttributeInfo
{
public:
    QString attrName;
    QString displayName;
    QVariant defaultValue;
    QString defaultValueStr;
    bool visible;
    QString interfaceType;
    QString codeInterface;
    QString colorGroup;
    QMap<int, QString> dropDownKeys;
    QMap<int, QString> dropDownValues;

    bool isDropDown() const;
    bool isNumber() const;
    bool isTextField() const;
    bool isMultiLine() const;
    bool isColor() const;
    bool isFont() const;
    bool isFile() const;
    bool isPageLink() const;
    bool isObjectList() const;
    bool isExternalEditor() const;

    bool equalsToDefault(const QVariant &v) const;

    QVariant getDropDownValue(const QVariant &srcValue) const;
};

class VdomTypeInfo
{
public:
    QString typeName;
    QString displayName;
    QString category;
    QString container;
    QStringList containers;
    QString renderType;
    QString iconId;
    QIcon icon;
    QMap<QString, AttributeInfo> attributes;
    QMap<QString, QMap<QString, QString> > lang;

    bool isContainer() const;
    bool isTopContainer() const;
    QMap<QString, AttributeInfo>::const_iterator findAttribute(const QString &name, bool translate = true) const;
    bool hasAttribute(const QString &name, bool translate = true) const;
};

QMap<QString, VdomTypeInfo> LoadTypes(const QString &filename);
QString TranslateAttributeVdomToQml(const QString &typeName, const QString &attrName);
QString TranslateAttributeQmlToVdom(const QString &typeName, const QString &attrName);

#endif // TYPESLOADER_H
