#ifndef VDOMCLASSFACTORY_H
#define VDOMCLASSFACTORY_H

#include <QString>
#include "vdomtypeswidget.h"

class VDOMWidget: public VdomTypesWidget
{
public:
    VDOMWidget(QWidget *parent) : VdomTypesWidget(parent) {}
};

VDOMWidget* createVdomWidget(const QString &typeName, QWidget *parent);

#endif // VDOMCLASSFACTORY_H
