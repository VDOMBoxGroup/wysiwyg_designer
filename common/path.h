#ifndef PATH_H
#define PATH_H

#include <QString>

// default paths relative to the application module directory
// or working data directory under temporary path
static const QString defaultWidgetsFileName = "/widgets.xml";
static const QString defaultPluginPath = "/designer";
static const QString defaultResourcePath = "/resources";
static const QString defaultTypesFileName = "/types.xml";
static const QString defaultTempDirPath = "/vdom/wysiwygeditor";

// create working data directory under temporary path
void MakeTempPath();

// return application executable directory
QString CurrentPath();

// return full path under application executable directory
QString DefaultPath(const QString &p);

// return resources path under working data directory
QString DefaultResourcePath();

// return widgets file path under working data directory
QString DefaultWidgetsFilePath();

#endif // PATH_H
