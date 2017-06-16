#ifndef VDOMTYPESWIDGET_H
#define VDOMTYPESWIDGET_H

#include <QWidget>
#include <QtDesigner/QDesignerExportWidget>
#include <QSharedPointer>
#include <QList>
#include "typesloader.h"
#include "wysiwyg.h"

class QDESIGNER_WIDGET_EXPORT VdomTypesWidget: public QWidget
{
    Q_OBJECT

public:
    VdomTypesWidget(QWidget *parent = 0);
    void setVdomType(const QSharedPointer<VdomTypeInfo> &typeInfo) { vdomType = typeInfo; }
    const QSharedPointer<VdomTypeInfo>& getVdomType() const { return vdomType; }
    void setWysiwyg(const WItem &w);
    void updateWysiwyg();
    void updateZindex();
    int zindex() { return globalZindex; }

protected:
    void paintEvent(QPaintEvent *event);

private:
    void removeChildWidgets();
    void removeChild(QWidget*);
    void createChildWidgets(QWidget *parent, const WItem &w);

private:
    QSharedPointer<VdomTypeInfo> vdomType;
    WItem wysiwyg;
    int baseZindex;
    int globalZindex;
};

#endif // VDOMTYPESWIDGET_H
