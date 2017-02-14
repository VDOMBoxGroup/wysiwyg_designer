#ifndef DESIGNER_H
#define DESIGNER_H

#include <qglobal.h>

class QWidget;
class DesignerCore;

class DesignerSignalHandler
{
public:
    virtual void widgetManaged(QWidget*) = 0;
};

class Designer
{
public:
    explicit Designer();
    virtual ~Designer();

    void initialize(QWidget *parent, DesignerSignalHandler *handler,
                    const QString &widgetsFileName, const QString &pluginPath);

    void setContent(const QString &content);
    QString getContent() const;

    QWidget* widgetBox() const;
    QWidget* form() const;
    QWidget* objectInspector() const;
    QWidget* propertyEditor() const;

private:
    DesignerCore *core;

    Q_DISABLE_COPY(Designer)
};

#endif // DESIGNER_H
