#ifndef TYPESLOADER_H
#define TYPESLOADER_H

#include <QStringList>
#include <QMap>

class AttributeInfo
{
public:
    QString attrName;
    QString displayName;
    QString defaultValue;
    bool visible;
    QString interfaceType;
    QString codeInterface;
    QString colorGroup;
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
