#include "vdomxml.h"
#include "util.h"
#include <QXmlStreamReader>
#include <QBuffer>

#define ATTRIBUTE "attribute"

bool VdomXmlItem::isEmpty() const
{
    return name.isEmpty();
}

bool VdomXmlItem::operator==(const VdomXmlItem &v) const
{
    return (name == v.name && attr == v.attr && child == v.child);
}

bool VdomXmlItem::operator!=(const VdomXmlItem &v) const
{
    return !(*this == v);
}

QString VdomXmlItem::strAttr(const QString &name) const
{
    QMap<QString, QString>::const_iterator i = attr.find(name);
    return (i != attr.end()) ? i.value() : QString();
}

QString VdomXmlItem::objectName() const
{
    return strAttr("name");
}

QList<VdomXmlItem>::const_iterator VdomXmlItem::findChild(const QString &name) const
{
    for(QList<VdomXmlItem>::const_iterator i=child.begin(); i!=child.end(); i++)
        if (i->objectName() == name)
            return i;
    return child.end();
}

// return first object that differs between two VdomXmlItems
// supported cases are:
// - creating a new object
// - modifying object attribute (except top and left)
const VdomXmlItem* VdomXmlItem::firstDiff(const VdomXmlItem &old) const
{
    // check attributes of this object
    if (attr != old.attr) {
        QMap<QString, QString> diff1 = attr - old.attr;
        QMap<QString, QString> diff2 = old.attr - attr;
        for(QMap<QString, QString>::const_iterator i=diff1.begin(); i!=diff1.end(); i++)
            if (i.key() != "top" && i.key() != "left")
                return this;
        for(QMap<QString, QString>::const_iterator i=diff2.begin(); i!=diff2.end(); i++)
            if (i.key() != "top" && i.key() != "left")
                return this;
    }
    // check children
    for(QList<VdomXmlItem>::const_iterator i=child.begin(); i!=child.end(); i++) {
        QList<VdomXmlItem>::const_iterator j = old.findChild(i->objectName());
        if (j == old.child.end())
            return &(*i);  // found new object
        else {
            const VdomXmlItem *ret = i->firstDiff(*j);
            if (ret)
                return ret;
        }
    }
    return NULL;
}

void VdomXmlItem::makeVdomxml(QXmlStreamWriter &output, bool includeChildren) const
{
    QMap<QString, QString> longAttr;
    QRegExp space_quotes("[\"\\s]");

    output.writeStartElement(name.toUpper());
    for (QMap<QString, QString>::const_iterator i=attr.begin(); i!=attr.end(); i++)
        if (i.key() != "name"
            && (IsLongAttribute(i.value())
                || i.value().contains(space_quotes)))
            longAttr[i.key()] = i.value();
        else
            output.writeAttribute(i.key(), i.value());

    WriteLongAttributes(output, longAttr);

    if (includeChildren)
        for (QList<VdomXmlItem>::const_iterator i=child.begin(); i!=child.end(); i++)
            i->makeVdomxml(output, includeChildren);

    output.writeEndElement();
}

QString VdomXmlItem::getVdomxml(bool includeChildren) const
{
    QBuffer buffer;
    buffer.open(QBuffer::WriteOnly);
    QXmlStreamWriter output(&buffer);
    output.setAutoFormatting(true);
    makeVdomxml(output, includeChildren);
    return QString(buffer.buffer()).trimmed();
}

static VdomXmlItem ParseItem(QXmlStreamReader &xml)
{
    VdomXmlItem ret;

    ret.name = xml.name().toString().toLower();

    QXmlStreamAttributes attrs = xml.attributes();
    for (QXmlStreamAttributes::const_iterator i=attrs.begin(); i!=attrs.end(); i++)
        ret.attr[i->name().toString()] = i->value().toString();

    while (!xml.atEnd()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartElement) {
            if (equals(xml, ATTRIBUTE)) {
                QString attrName = attr(xml, "Name");
                ret.attr[attrName] = get(xml);
            } else
                ret.child.append(ParseItem(xml));
        } else if (token == QXmlStreamReader::EndElement && !equals(xml, ATTRIBUTE))
            break;
    }

    return ret;
}

//void print(const VdomXmlItem &w, int level=0)
//{
//    QString indent(level, '-');
//    qDebug(QString("%1%2").arg(indent).arg(w.name).toAscii().constData());
//    for (QList<VdomXmlItem>::const_iterator i=w.child.begin(); i!=w.child.end(); i++)
//        print(*i, level+1);
//}

VdomXmlItem ParseVdomxml(const QString &s)
{
    VdomXmlItem ret;

    QXmlStreamReader xml(s);

    while (!xml.atEnd()) {
        xml.readNextStartElement();
        if (xml.tokenType() == QXmlStreamReader::StartElement)
            ret = ParseItem(xml);
    }

    return ret;
}

void WriteAttribute(QXmlStreamWriter &output, const QString &name, const QString &value)
{
    output.writeStartElement("Attribute");
    output.writeAttribute("Name", name);
    output.writeCDATA(value);
    output.writeEndElement();
}

void WriteLongAttributes(QXmlStreamWriter &output, const QMap<QString, QString> &attr)
{
    for (QMap<QString, QString>::const_iterator i=attr.begin(); i!=attr.end(); i++)
        WriteAttribute(output, i.key(), i.value());
}
