#include "path.h"
#include <QCoreApplication>
#include <QFileInfo>
#include <QDir>

inline QString JoinPath(const QString &p1, const QString &p2)
{
    QString a = p1, b = p2, d = "/";
    if (a.endsWith(d))
        a.truncate(a.size() - d.size());
    if (b.startsWith(d))
        d = "";
    return a + d + b;
}

QString TempDirPath(const QString &p)
{
    static QString p1 = JoinPath(QDir::tempPath(), defaultTempDirPath);
    return JoinPath(p1, p);
}

void MakeTempPath()
{
    QDir().mkpath(TempDirPath(defaultResourcePath));
    //qDebug(TempDirPath("").toLatin1().constData());
}

QString CurrentPath()
{
    static QString appPath = QFileInfo(QCoreApplication::applicationFilePath()).absoluteDir().path();
    return appPath;
}

QString DefaultPath(const QString &p)
{
    return JoinPath(CurrentPath(), p);
}

QString DefaultResourcePath()
{
    return TempDirPath(defaultResourcePath);
}

QString DefaultWidgetsFilePath()
{
    return TempDirPath(defaultWidgetsFileName);
}
