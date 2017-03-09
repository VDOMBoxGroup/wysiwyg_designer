#include "util.h"

QColor parseColor(const QString &s)
{
    QString ss = s;
    if (ss.startsWith("#"))
        ss = ss.mid(1);
    int color = ss.toInt(0, 16);
    return QColor((color >> 16) & 0xFF,
                  (color >> 8) & 0xFF,
                  color & 0xFF);
}
