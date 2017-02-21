#ifndef PATH_H
#define PATH_H

#include <QString>

// default paths relative to the application module directory
static const QString defaultWidgetsFileName = "/widgets.xml";
static const QString defaultPluginPath = "/designer";
static const QString defaultTypesFileName = "/types.xml";

QString defaultPath(const QString &p);

#endif // PATH_H
