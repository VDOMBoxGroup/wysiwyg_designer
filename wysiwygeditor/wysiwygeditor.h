#ifndef WYSIWYGEDITOR_H
#define WYSIWYGEDITOR_H

#include <QObject>
#include "designer.h"

class QWidget;

class WysiwygEditor: public QObject, public DesignerSignalHandler
{
    Q_OBJECT
public:
    WysiwygEditor();
    virtual ~WysiwygEditor();

    Q_INVOKABLE void initialize(QWidget *parent,
                                const QString &widgetsFileName = QString(),
                                const QString &pluginPath = QString());

    Q_INVOKABLE void setContent(const QString &content = QString());
    Q_INVOKABLE QString getContent() const;

    Q_INVOKABLE QWidget* widgetBox() const;
    Q_INVOKABLE QWidget* form() const;
    Q_INVOKABLE QWidget* objectInspector() const;
    Q_INVOKABLE QWidget* propertyEditor() const;

private:
    void widgetManaged(QWidget*);

    Designer *designer;

    Q_DISABLE_COPY(WysiwygEditor)
};

#endif // WYSIWYGEDITOR_H
