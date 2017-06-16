#include "converter.h"
#include "path.h"
#include "util.h"
#include "vdomxml.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QBuffer>
#include <QSet>
#include <QMap>
#include <QRect>
#include <QFont>
#include <QFileInfo>

#define WIDGET "widget"
#define PROPERTY "property"
#define ATTRIBUTE "attribute"

const QMap<QString, VdomTypeInfo>& GetVdomTypes()
{
    static QMap<QString, VdomTypeInfo> types = LoadTypes(DefaultPath(defaultTypesFileName));
    return types;
}

QSet<QString> makeSkippedProperties()
{
    QSet<QString> ret;
    ret.insert("top");
    ret.insert("left");
    ret.insert("width");
    ret.insert("height");
    return ret;
}

static QSet<QString> skippedProperties = makeSkippedProperties();

// === QML -> VDOMXML

QRect rect(QXmlStreamReader &input)
{
    QRect ret;
    while (!input.atEnd() && !(input.tokenType() == QXmlStreamReader::EndElement && equals(input, "rect"))) {
        if (input.tokenType() == QXmlStreamReader::StartElement) {
            if (equals(input, "x"))
                ret.setX(get(input).toInt());
            else if (equals(input, "y"))
                ret.setY(get(input).toInt());
            else if (equals(input, "width"))
                ret.setWidth(get(input).toInt());
            else if (equals(input, "height"))
                ret.setHeight(get(input).toInt());
        }
        input.readNext();
    }
    return ret;
}

QColor color(QXmlStreamReader &input)
{
    QColor ret;
    while (!input.atEnd() && !(input.tokenType() == QXmlStreamReader::EndElement && equals(input, "color"))) {
        if (input.tokenType() == QXmlStreamReader::StartElement) {
            if (equals(input, "red"))
                ret.setRed(get(input).toInt());
            else if (equals(input, "green"))
                ret.setGreen(get(input).toInt());
            else if (equals(input, "blue"))
                ret.setBlue(get(input).toInt());
        }
        input.readNext();
    }
    return ret;
}

QFont font(QXmlStreamReader &input)
{
    QFont ret;
    while (!input.atEnd() && !(input.tokenType() == QXmlStreamReader::EndElement && equals(input, "font"))) {
        if (input.tokenType() == QXmlStreamReader::StartElement && equals(input, "family"))
            ret.setFamily(get(input));
        input.readNext();
    }
    return ret;
}

QString readPropertyValue(QXmlStreamReader &input, const AttributeInfo &attr, QStringList &resources)
{
    input.readNextStartElement();
    if (input.name() == "color") {
        QColor c = color(input);
        int cc = (c.red() << 16) | (c.green() << 8) | c.blue();
        return QString::number(cc, 16);
    } else if (input.name() == "font") {
        return font(input).family();
    } else if (input.name() == "bool") {
        QString data = get(input);
        if (data == "true")
            return "1";
        else if (data == "false")
            return "0";
        else
            return data;
    } else if (attr.isDropDown()) {
        QString data = get(input);
        QMap<int, QString>::const_iterator i = FindFirst(attr.dropDownValues, data);
        if (i != attr.dropDownValues.end())
            return attr.dropDownKeys[i.key()];
        else
            return data;
    } else if (attr.isFile()) {
        QString data = get(input);
        if (QFileInfo(data).exists() && !resources.contains(data))
            resources.push_back(data);
        return data;
    } else
        return get(input);
}

void vdomobjectProperty(QXmlStreamReader &input, QXmlStreamWriter &output,
                        QMap<QString, QString> &longProperties,
                        const VdomTypeInfo &type, QStringList &resources)
{
    QString name = attr(input, "name");
    if (skippedProperties.contains(name)) {
        input.skipCurrentElement();
        return;
    }
    if (name == "geometry") {
        QRect r = rect(input);
        output.writeAttribute("top", QString::number(r.y()));
        output.writeAttribute("left", QString::number(r.x()));
        output.writeAttribute("width", QString::number(r.width()));
        output.writeAttribute("height", QString::number(r.height()));
    } else {
        if (!type.attributes.contains(name) || !type.attributes[name].visible) {
            input.skipCurrentElement();
            return;
        }
        QString value = readPropertyValue(input, type.attributes[name], resources);
        if (IsLongAttribute(value))
            longProperties[name] = value;
        else
            output.writeAttribute(name, value);
    }
}

void widgetToVdomobject(QXmlStreamReader &input, QXmlStreamWriter &output,
                        const QString &parentTypeName, QStringList &resources,
                        QStringList &errors)
{
    QMap<QString, QString> longProperties;

    const QMap<QString, VdomTypeInfo> &types = GetVdomTypes();

    QString typeName = attr(input, "class").toLower();
    if (!types.contains(typeName)) {
        errors.append(QString("Unknown VDOM type \'%1\'").arg(typeName));
        input.skipCurrentElement();
        return;
    }

    QString objName = attr(input, "name");

    const VdomTypeInfo &type = types[typeName];
    if (!parentTypeName.isEmpty() && !type.containers.contains(parentTypeName)) {
        errors.append(QString("Object \'%1\' of type \'%2\' can't be placed inside \'%3\'")
                      .arg(objName).arg(capitalize(typeName)).arg(capitalize(parentTypeName)));
        input.skipCurrentElement();
        return;
    }

    output.writeStartElement(typeName.toUpper());
    output.writeAttribute("name", objName);

    while (!input.atEnd()) {
        QXmlStreamReader::TokenType token = input.readNext();
        if (token == QXmlStreamReader::StartElement) {
            if (equals(input, WIDGET))
                widgetToVdomobject(input, output, typeName, resources, errors);
            else if (equals(input, PROPERTY))
                vdomobjectProperty(input, output, longProperties, type, resources);
        } else if (token == QXmlStreamReader::EndElement && equals(input, WIDGET))
            break;
    }

    WriteLongAttributes(output, longProperties);

    output.writeEndElement();
}

QString QmlToVdomxml(const QString &qml, QStringList &resources, QStringList &errors)
{
    QXmlStreamReader input(qml);

    QBuffer buffer;
    buffer.open(QBuffer::WriteOnly);
    QXmlStreamWriter output(&buffer);
    output.setAutoFormatting(true);

    while (!input.atEnd()) {
        input.readNextStartElement();
        if (input.tokenType() == QXmlStreamReader::StartElement && equals(input, WIDGET))
            widgetToVdomobject(input, output, "", resources, errors);
    }

    return QString(buffer.buffer()).trimmed();
}

QString QmlToVdomxml(const QString &qml, QStringList &resources)
{
    QStringList e;
    return QmlToVdomxml(qml, resources, e);
}

// === VDOMXML -> QML

void widgetProperty(QXmlStreamWriter &output, const QString &name, const QString &value, const AttributeInfo &attr)
{
    output.writeStartElement(PROPERTY);
    output.writeAttribute("name", name);
    if (attr.isNumber())
        output.writeTextElement("number", value);
    else if (attr.isColor()) {
        QColor c = ParseColor(value);
        output.writeStartElement("color");
        output.writeTextElement("red", QString::number(c.red()));
        output.writeTextElement("green", QString::number(c.green()));
        output.writeTextElement("blue", QString::number(c.blue()));
        output.writeEndElement();
    } else if (attr.isFont()) {
        output.writeStartElement("font");
        output.writeTextElement("family", value);
        output.writeEndElement();
    } else if (attr.isDropDown()) {
        QMap<int, QString>::const_iterator i = FindFirst(attr.dropDownKeys, value);
        if (i == attr.dropDownKeys.end())
            i = FindFirst(attr.dropDownKeys, attr.defaultValueStr);
        if (i != attr.dropDownKeys.end())
            output.writeTextElement("enum", attr.dropDownValues[i.key()]);
    } else if (attr.isFile())
        output.writeTextElement("pixmap", value);
    else
        output.writeTextElement("cstring", value);
    output.writeEndElement();
}

void widgetGeometry(QXmlStreamReader &input, QXmlStreamWriter &output)
{
    output.writeStartElement(PROPERTY);
    output.writeAttribute("name", "geometry");
    output.writeStartElement("rect");
    output.writeTextElement("x", attr(input, "left"));
    output.writeTextElement("y", attr(input, "top"));
    output.writeTextElement("width", attr(input, "width"));
    output.writeTextElement("height", attr(input, "height"));
    output.writeEndElement();
    output.writeEndElement();
}

void vdomobjectToWidget(QXmlStreamReader &input, QXmlStreamWriter &output, QMap<QString, bool> &customWidgets)
{
    const QMap<QString, VdomTypeInfo> &types = GetVdomTypes();

    QString typeName = input.name().toString().toLower();
    if (!types.contains(typeName)) {
        input.skipCurrentElement();
        return;
    }

    const VdomTypeInfo &type = types[typeName];

    QString objectName = attr(input, "name");
    if (customWidgets.isEmpty())
        output.writeTextElement("class", objectName);

    customWidgets[typeName] = type.isContainer();

    output.writeStartElement(WIDGET);
    output.writeAttribute("class", capitalize(typeName));
    output.writeAttribute("name", objectName);

    widgetGeometry(input, output);

    QXmlStreamAttributes attrs = input.attributes();
    for (QXmlStreamAttributes::const_iterator i=attrs.begin(); i!=attrs.end(); i++) {
        QString attrName = i->name().toString();
        if (!skippedProperties.contains(attrName) && type.attributes.contains(attrName))
            widgetProperty(output, attrName, i->value().toString(), type.attributes[attrName]);
    }

    while (!input.atEnd()) {
        QXmlStreamReader::TokenType token = input.readNext();
        if (token == QXmlStreamReader::StartElement) {
            if (equals(input, ATTRIBUTE)) {
                QString attrName = attr(input, "Name");
                if (type.attributes.contains(attrName))
                    widgetProperty(output, attrName, get(input), type.attributes[attrName]);
            } else
                vdomobjectToWidget(input, output, customWidgets);
        } else if (token == QXmlStreamReader::EndElement && !equals(input, ATTRIBUTE))
            break;
    }

    output.writeEndElement();
}

void writeCustomWidgets(QXmlStreamWriter &output, const QMap<QString, bool> &customWidgets)
{
    output.writeStartElement("customwidgets");

    for (QMap<QString, bool>::const_iterator i=customWidgets.begin(); i!=customWidgets.end(); i++) {
        output.writeStartElement("customwidget");
        output.writeTextElement("class", capitalize(i.key()));
        if (i.value())
            output.writeTextElement("container", "1");
        output.writeEndElement();
    }

    output.writeEndElement();
}

QString VdomxmlToQml(const QString &vdomxml)
{
    QXmlStreamReader input(vdomxml);

    QBuffer buffer;
    buffer.open(QBuffer::WriteOnly);
    QXmlStreamWriter output(&buffer);
    output.setAutoFormatting(true);
    output.writeStartDocument();
    output.writeStartElement("ui");
    output.writeAttribute("version", "4.0");

    QMap<QString, bool> customWidgets;

    while (!input.atEnd()) {
        input.readNextStartElement();
        if (input.tokenType() == QXmlStreamReader::StartElement)
            vdomobjectToWidget(input, output, customWidgets);
    }

    writeCustomWidgets(output, customWidgets);

    output.writeEndElement();
    output.writeEndDocument();
    return QString(buffer.buffer()).trimmed();
}
