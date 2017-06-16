#include "wysiwyg.h"
#include "util.h"
#include <QXmlStreamReader>
#include <QSet>

#define CONTAINER "container"

static QSet<QString> MakeFinalTags()
{
    QSet<QString> ret;
    ret.insert("text");
    ret.insert("htmltext");
    ret.insert("svg");
    return ret;
}

static QSet<QString> finalTags = MakeFinalTags();

int WItem::intAttr(const QString &name) const
{
    return strAttr(name).toInt();
}

QString WItem::strAttr(const QString &name) const
{
    QMap<QString, QString>::const_iterator i = attr.find(name);
    return (i != attr.end()) ? i.value() : QString();
}

bool WItem::isEmpty() const
{
    return name.isEmpty();
}

QString WItem::objectName() const
{
    return strAttr("name");
}

inline bool IsNewObject(const WItem &w)
{
    return (w.name.toLower() == CONTAINER && !w.objectName().isEmpty());
}

static WItem ParseItem(QXmlStreamReader &xml, QList<WItem> &l)
{
    WItem ret;

    ret.name = xml.name().toString().toLower();

    QXmlStreamAttributes attrs = xml.attributes();
    for (QXmlStreamAttributes::const_iterator i=attrs.begin(); i!=attrs.end(); i++)
        ret.attr[i->name().toString()] = i->value().toString();

    if (finalTags.contains(ret.name)) {
        ret.value = GetElementXml(xml).trimmed();
        //qDebug("Final \'%s\': \'%s\'", ret.name.toLatin1().constData(), ret.value.toLatin1().constData());
    } else {
        while (!xml.atEnd()) {
            QXmlStreamReader::TokenType token = xml.readNext();
            if (token == QXmlStreamReader::StartElement) {
                WItem child = ParseItem(xml, l);
                if (!IsNewObject(child))
                    ret.child.append(child);
                else
                    l.prepend(child);
            }
            else if (token == QXmlStreamReader::EndElement)
                break;
        }
    }

    return ret;
}

//void print(const WItem &w, int level=0)
//{
//    QString indent(level, '-');
//    qDebug(QString("%1%2").arg(indent).arg(w.name).toAscii().constData());
//    for (QList<WItem>::const_iterator i=w.child.begin(); i!=w.child.end(); i++)
//        print(*i, level+1);
//}

QList<WItem> ParseWysiwyg(const QString &s)
{
    QList<WItem> l;

    QXmlStreamReader xml(s);

    while (!xml.atEnd()) {
        xml.readNextStartElement();
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            WItem w = ParseItem(xml, l);
            if (IsNewObject(w))
                l.prepend(w);
        }
    }

    return l;
}
