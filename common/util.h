#ifndef UTIL_H
#define UTIL_H

#include <QColor>
#include <QString>
#include <Map>

QColor parseColor(const QString &s);

template<typename K, typename V>
typename QMap<K, V>::const_iterator FindFirst(const QMap<K, V> &m, const V &v)
{
    for (typename QMap<K, V>::const_iterator i=m.begin(); i!=m.end(); i++)
        if (i.value() == v)
            return i;
    return m.end();
}

#endif // UTIL_H
