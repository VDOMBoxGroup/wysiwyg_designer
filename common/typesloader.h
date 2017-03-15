#ifndef TYPESLOADER_H
#define TYPESLOADER_H

#include <QStringList>
#include <QMap>
#include <QVariant>

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
    QMap<QString, AttributeInfo> attributes;
    QMap<QString, QMap<QString, QString> > lang;

    bool isContainer() const;
    bool isTopContainer() const;
};

QMap<QString, VdomTypeInfo> LoadTypes(const QString &filename);

#endif // TYPESLOADER_H
