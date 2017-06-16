#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QVariant>
#include "wysiwygeditor.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    bool init();
    ~Dialog();

private slots:
    void onChanged();
    void onAttrChanged(const QObject &object, const QString &name, const QVariant &value);

private:
    void setContent();

private:
    Ui::Dialog *ui;

    WysiwygEditor editor;
};

#endif // DIALOG_H
