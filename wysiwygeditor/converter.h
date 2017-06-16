#ifndef CONVERTER_H
#define CONVERTER_H

#include <QStringList>
#include "typesloader.h"

QString QmlToVdomxml(const QString &qml, QStringList &resources);
QString QmlToVdomxml(const QString &qml, QStringList &resources, QStringList &errors);
QString VdomxmlToQml(const QString &vdomxml);

const QMap<QString, VdomTypeInfo>& GetVdomTypes();

#endif // CONVERTER_H
