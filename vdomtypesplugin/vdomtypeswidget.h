#ifndef VDOMTYPESWIDGET_H
#define VDOMTYPESWIDGET_H

#include <QWidget>
#include <QtDesigner/QDesignerExportWidget>

class QDESIGNER_WIDGET_EXPORT VdomTypesWidget: public QWidget
{
    Q_OBJECT

public:
    VdomTypesWidget(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // VDOMTYPESWIDGET_H
