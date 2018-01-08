#ifndef VDOMXML_H
#define VDOMXML_H

#include <QString>
#include <QMap>
#include <QList>
#include <QXmlStreamWriter>

#define MAX_ATTR_LEN 20

class VdomXmlItem
{
public:
    QString name;
    QMap<QString, QString> attr;
    QList<VdomXmlItem> child;

    bool isEmpty() const;
    bool operator==(const VdomXmlItem&) const;
    bool operator!=(const VdomXmlItem&) const;

    QString strAttr(const QString &name) const;
    QString objectName() const;

    QList<VdomXmlItem>::const_iterator findChild(const QString &name) const;

    const VdomXmlItem* firstDiff(const VdomXmlItem&) const;

    QString getVdomxml(bool includeChildren=false) const;
    void makeVdomxml(QXmlStreamWriter&, bool) const;
};

VdomXmlItem ParseVdomxml(const QString &s);

void WriteAttribute(QXmlStreamWriter &output, const QString &name, const QString &value);

bool IsLongAttribute(const QString &name, const QString &value);

void WriteLongAttributes(QXmlStreamWriter &output, const QMap<QString, QString> &attr);

#endif // VDOMXML_H
