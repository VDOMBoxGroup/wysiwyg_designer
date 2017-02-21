#include "vdomclassfactory.h"
#include "vdomclasses.h"

VDOMWidget* createVdomWidget(const QString &typeName, QWidget *parent)
{
    QMap<QString, FactoryFunction>::const_iterator i = factory.find(typeName);
    if (i != factory.end())
        return i.value()(parent);
    return NULL;
}
