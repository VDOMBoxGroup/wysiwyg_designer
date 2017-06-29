#ifndef UTIL_H
#define UTIL_H

#include <QColor>
#include <QString>
#include <Map>
#include <QXmlStreamReader>

QColor ParseColor(const QString &s);

template<typename K, typename V>
typename QMap<K, V>::const_iterator FindFirst(const QMap<K, V> &m, const V &v)
{
    for (typename QMap<K, V>::const_iterator i=m.begin(); i!=m.end(); i++)
        if (i.value() == v)
            return i;
    return m.end();
}

template<typename K, typename V>
QMap<K, V> operator-(const QMap<K, V> &m1, const QMap<K, V> &m2)
{
    QMap<K, V> ret;
    for (typename QMap<K, V>::const_iterator i=m1.begin(); i!=m1.end(); i++) {
        typename QMap<K, V>::const_iterator j = m2.find(i.key());
        if (j == m2.end() || i.value() != j.value())
            ret.insert(i.key(), i.value());
    }
    return ret;
}

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

QString GetElementXml(QXmlStreamReader &xml);

bool WriteFile(const QString &fname, const QByteArray &data, bool binary = false);
bool WriteFile(const QString &fname, const QString &data, bool binary = false);
QByteArray ReadFile(const QString &fname, bool binary = false);

#endif // UTIL_H
