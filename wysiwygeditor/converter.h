#ifndef CONVERTER_H
#define CONVERTER_H

#include <QString>
#include "typesloader.h"

QString qmlToVdomxml(const QString &qml);
QString vdomxmlToQml(const QString &vdomxml);

const QMap<QString, VdomTypeInfo>& getVdomTypes();

#endif // CONVERTER_H
