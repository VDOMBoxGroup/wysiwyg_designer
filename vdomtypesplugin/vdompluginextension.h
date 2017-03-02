#ifndef VDOMPLUGINEXTENSION_H
#define VDOMPLUGINEXTENSION_H

#include <QtDesigner/QExtensionFactory>
#include <QtDesigner/QDesignerPropertySheetExtension>
#include <QMap>

class QExtensionManager;
class VdomTypesWidget;

class VdomPluginExtensionFactory: public QExtensionFactory
{
    Q_OBJECT

public:
    VdomPluginExtensionFactory(QExtensionManager *parent = 0);

protected:
    QObject* createExtension(QObject *object, const QString &iid, QObject *parent) const;
};

class VdomPluginPropertySheetExtension: public QObject, public QDesignerPropertySheetExtension
{
    Q_OBJECT
    Q_INTERFACES(QDesignerPropertySheetExtension)

public:
    VdomPluginPropertySheetExtension(VdomTypesWidget *widget, QObject *parent);

    int count() const;
    int indexOf(const QString &name) const;
    QString propertyName(int index) const ;
    QString propertyGroup(int index) const;
    void setPropertyGroup(int index, const QString &group);
    bool hasReset(int index) const;
    bool reset(int index);
    bool isVisible(int index) const;
    void setVisible(int index, bool b);
    bool isAttribute(int index) const;
    void setAttribute(int index, bool b);
    QVariant property(int index) const;
    void setProperty(int index, const QVariant &value);
    bool isChanged(int index) const;
    void setChanged(int index, bool changed);

private:
    void registerProperty(const QString &name);
    void registerProperties(const QString &groupName);

    VdomTypesWidget *myWidget;
    QMap<QString, int> indexes;
    QMap<int, QString> names;
};

#endif // VDOMPLUGINEXTENSION_H
