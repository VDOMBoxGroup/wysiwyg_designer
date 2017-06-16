#include "util.h"
#include <QXmlStreamWriter>
#include <QBuffer>
#include <QFile>

QColor ParseColor(const QString &s)
{
    QString ss = s;
    if (ss.startsWith("#"))
        ss = ss.mid(1);
    int color = ss.toInt(0, 16);
    return QColor((color >> 16) & 0xFF,
                  (color >> 8) & 0xFF,
                  color & 0xFF);
}

QString GetElementXml(QXmlStreamReader &xml)
{
    QBuffer buffer;
    buffer.open(QBuffer::WriteOnly);

    QXmlStreamWriter out(&buffer);

    QString tagName = xml.name().toString();
    int count = 1;

    while (!xml.atEnd()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        //qDebug(xml.name().toString().toLatin1().constData());
        //qDebug("token %d", (int)token);
        if (token == QXmlStreamReader::StartElement) {
            if (!xml.name().compare(tagName))
                count++;
            out.writeStartElement(xml.name().toString());
            out.writeAttributes(xml.attributes());
        } else if (token == QXmlStreamReader::EndElement) {
            if (!xml.name().compare(tagName)) {
                count--;
                if (!count)
                    break;
            }
            out.writeEndElement();
        } else if (token == QXmlStreamReader::Characters) {
            out.writeCharacters(xml.text().toString());
        }
    }

    return buffer.buffer();
}

void WriteFile(const QString &fname, const QByteArray &data)
{
    QFile file(fname);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug("Can't open file \'%s\': %s", fname.toLatin1().constData(), file.errorString().toLatin1().constData());
        return;
    }
    file.write(data);
}

void WriteFile(const QString &fname, const QString &data)
{
    QByteArray a;
    a.append(data);
    WriteFile(fname, a);
}
