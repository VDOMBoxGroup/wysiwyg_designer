#ifndef WYSIWYG_H
#define WYSIWYG_H

#include <QString>
#include <QMap>
#include <QList>

class WItem
{
public:
    QString name;
    QMap<QString, QString> attr;
    QList<WItem> child;
    QString value;

    int intAttr(const QString &name) const;
    QString strAttr(const QString &name) const;

    bool isEmpty() const;

    QString objectName() const;
};

QList<WItem> ParseWysiwyg(const QString &s);

#endif // WYSIWYG_H
