#include "path.h"
#include <QCoreApplication>
#include <QFileInfo>
#include <QDir>

QString defaultPath(const QString &p)
{
    static QString appPath = QFileInfo(QCoreApplication::applicationFilePath()).absoluteDir().path();
    return appPath + p;
}
