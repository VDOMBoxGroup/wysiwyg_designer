#ifndef DESIGNER_H
#define DESIGNER_H

#include <QVariant>

class QWidget;
class DesignerCore;

class DesignerSignalHandler
{
public:
    virtual void widgetManaged(QWidget*) = 0;
    virtual void widgetRemoved(QWidget*) = 0;
    virtual void changed() = 0;
    virtual void propertyChanged(const QObject &object, const QString &name, const QVariant &value) = 0;
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
