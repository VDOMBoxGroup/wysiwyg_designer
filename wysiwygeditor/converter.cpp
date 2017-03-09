#include "converter.h"
#include "path.h"
#include "util.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QBuffer>
#include <QSet>
#include <QMap>
#include <QRect>
#include <QFont>

#define WIDGET "widget"
#define PROPERTY "property"
#define ATTRIBUTE "attribute"
#define MAX_ATTR_LEN 20

const QMap<QString, VdomTypeInfo>& getVdomTypes()
{
    static QMap<QString, VdomTypeInfo> types = LoadTypes(defaultPath(defaultTypesFileName));
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

inline bool equals(const QXmlStreamReader &xml, const QString &str)
{
    return (xml.name().compare(str, Qt::CaseInsensitive) == 0);
}

inline QString attr(const QXmlStreamReader &xml, const QString &name)
{
    return xml.attributes().value(name).toString();
}

inline QString get(QXmlStreamReader &xml)
{
    return xml.readElementText().trimmed();
}

inline QString capitalize(const QString &s)
{
    return s.left(1).toUpper() + s.mid(1);
}

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

void writeAttribute(QXmlStreamWriter &output, const QString &name, const QString &value)
{
    output.writeStartElement("Attribute");
    output.writeAttribute("Name", name);
    output.writeCDATA(value);
    output.writeEndElement();
}

QString readPropertyValue(QXmlStreamReader &input)
{
    input.readNextStartElement();
    if (input.name() == "color") {
        QColor c = color(input);
        int cc = (c.red() << 16) | (c.green() << 8) | c.blue();
        return QString::number(cc, 16);
    } else if (input.name() == "font") {
        return font(input).family();
    } else
        return get(input);
}

void vdomobjectProperty(QXmlStreamReader &input, QXmlStreamWriter &output,
                        QMap<QString, QString> &longProperties)
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
        QString value = readPropertyValue(input);
        if (value.length() <= MAX_ATTR_LEN)
            output.writeAttribute(name, value);
        else
            longProperties[name] = value;
    }
}

void widgetToVdomobject(QXmlStreamReader &input, QXmlStreamWriter &output)
{
    QMap<QString, QString> longProperties;

    const QMap<QString, VdomTypeInfo> &types = getVdomTypes();

    QString typeName = attr(input, "class").toLower();
    if (!types.contains(typeName)) {
        input.skipCurrentElement();
        return;
    }

    output.writeStartElement(typeName.toUpper());
    output.writeAttribute("name", attr(input, "name"));

    while (!input.atEnd()) {
        QXmlStreamReader::TokenType token = input.readNext();
        if (token == QXmlStreamReader::StartElement) {
            if (equals(input, WIDGET))
                widgetToVdomobject(input, output);
            else if (equals(input, PROPERTY))
                vdomobjectProperty(input, output, longProperties);
        } else if (token == QXmlStreamReader::EndElement && equals(input, WIDGET))
            break;
    }

    for (QMap<QString, QString>::const_iterator i=longProperties.begin(); i!=longProperties.end(); i++)
        writeAttribute(output, i.key(), i.value());

    output.writeEndElement();
}

QString qmlToVdomxml(const QString &qml)
{
    QXmlStreamReader input(qml);

    QBuffer buffer;
    buffer.open(QBuffer::WriteOnly);
    QXmlStreamWriter output(&buffer);
    output.setAutoFormatting(true);

    while (!input.atEnd()) {
        input.readNextStartElement();
        if (input.tokenType() == QXmlStreamReader::StartElement && equals(input, WIDGET))
            widgetToVdomobject(input, output);
    }

    return QString(buffer.buffer()).trimmed();
}

// === VDOMXML -> QML

void widgetProperty(QXmlStreamWriter &output, const QString &name, const QString &value, const AttributeInfo &attr)
{
    output.writeStartElement(PROPERTY);
    output.writeAttribute("name", name);
    if (attr.isNumber())
        output.writeTextElement("number", value);
    else if (attr.isColor()) {
        QColor c = parseColor(value);
        output.writeStartElement("color");
        output.writeTextElement("red", QString::number(c.red()));
        output.writeTextElement("green", QString::number(c.green()));
        output.writeTextElement("blue", QString::number(c.blue()));
        output.writeEndElement();
    }
    else if (attr.isFont()) {
        output.writeStartElement("font");
        output.writeTextElement("family", value);
        output.writeEndElement();
    }
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
    const QMap<QString, VdomTypeInfo> &types = getVdomTypes();

    QString typeName = input.name().toString().toLower();
    if (!types.contains(typeName)) {
        input.skipCurrentElement();
        return;
    }

    const VdomTypeInfo &type = types[typeName];

    QString objectName = attr(input, "name");
    if (customWidgets.isEmpty())
        output.writeTextElement("class", objectName);

    const QString &container = type.container;
    customWidgets[typeName] = (container == "2" || container == "3");

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

QString vdomxmlToQml(const QString &vdomxml)
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
