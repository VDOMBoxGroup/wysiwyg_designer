#ifndef VDOMTYPESWIDGET_H
#define VDOMTYPESWIDGET_H

#include <QWidget>
#include <QtDesigner/QDesignerExportWidget>
#include <QSharedPointer>
#include "typesloader.h"

class QDESIGNER_WIDGET_EXPORT VdomTypesWidget: public QWidget
{
    Q_OBJECT

public:
    VdomTypesWidget(QWidget *parent = 0);
    void setVdomType(const QSharedPointer<VdomTypeInfo> &typeInfo) { vdomType = typeInfo; }
    const QSharedPointer<VdomTypeInfo>& getVdomType() const { return vdomType; }

protected:
    void paintEvent(QPaintEvent *event);

private:
    QSharedPointer<VdomTypeInfo> vdomType;
};

#endif // VDOMTYPESWIDGET_H
