#ifndef WIDGETSFILE_H
#define WIDGETSFILE_H

#include <QString>
#include <QByteArray>

QByteArray CreateWidgetsXml();
void WriteWidgetsFile(const QString &widgetsFile, const QByteArray &data);

#endif // WIDGETSFILE_H
