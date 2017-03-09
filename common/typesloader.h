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

    bool isNumber() const;
    bool isTextField() const;
    bool isMultiLine() const;
    bool isColor() const;
    bool isFont() const;

    bool equalsToDefault(const QVariant &v) const;
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
};

QMap<QString, VdomTypeInfo> LoadTypes(const QString &filename);

#endif // TYPESLOADER_H
