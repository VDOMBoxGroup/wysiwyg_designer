#include "widgetsfile.h"
#include <QFile>
#include <QBuffer>
#include <QXmlStreamWriter>

QByteArray CreateWidgetsXml()
{
    QBuffer buffer;
    buffer.open(QBuffer::WriteOnly);

    QXmlStreamWriter xml(&buffer);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();

    xml.writeStartElement("widgetbox");
    xml.writeEndElement(); // widgetbox

    xml.writeEndDocument();

    return buffer.buffer();
}

void WriteWidgetsFile(const QString &widgetsFile, const QByteArray &data)
{
    QFile file(widgetsFile);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug("Can't open widgets file \'%s\': %s", widgetsFile.toLatin1().constData(), file.errorString().toLatin1().constData());
        return;
    }
    file.write(data);
}
