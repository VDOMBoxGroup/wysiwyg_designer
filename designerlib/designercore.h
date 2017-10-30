#ifndef DESIGNER_CORE_H
#define DESIGNER_CORE_H

#include <QObject>
#include <QMap>
#include "designer.h"

class QWidget;
class QDesignerFormEditorInterface;
class QDesignerFormWindowManagerInterface;
class QDesignerFormWindowInterface;
namespace SharedTools {
    class WidgetHost;
}

class DesignerCore: public QObject
{
    Q_OBJECT
public:
    explicit DesignerCore(QWidget *parent, DesignerSignalHandler *handler,
                          const QString &widgetsFileName,
                          const QString &pluginPath);
    virtual ~DesignerCore();

    QWidget* getWidgetBox() const;
    QWidget* getForm() const;
    QWidget* getObjectInspector() const;
    QWidget* getPropertyEditor() const;

    void setContent(const QString &content);
    QString getContent() const;

    QString getSelectionName() const { return selection; }
    QString getSelectionType() const { return selectionType; }
    QMap<QString, QString> getObjects() const;

Q_SIGNALS:
    void selectionChanged(const QString &newSelection, const QString &oldSelection) const;

private slots:
    void formSizeChanged(int w, int h);
    void widgetManaged(QWidget *widget);
    void widgetRemoved(QWidget *widget);
    void changed();
    void propertyChanged(const QString &name, const QVariant &value);
    void onSelectionChanged();

private:
    void createDesignerCore(QWidget *parent, const QString &widgetsFileName,
                            const QString &pluginPath);
    void initializeCorePlugins(const QString &pluginPath);
    void hidePropertyEditorButtons(QObject *editor);

    QDesignerFormEditorInterface *core;
    QDesignerFormWindowManagerInterface *formWindowManager;
    QWidget *signalSlotEditor;
    QWidget *resourceEditor;
    QDesignerFormWindowInterface *formWindow;
    SharedTools::WidgetHost *widgetHost;

    DesignerSignalHandler *signalHandler;

    QString selection;
    QString selectionType;

    Q_DISABLE_COPY(DesignerCore)
};

#endif // DESIGNER_CORE_H
