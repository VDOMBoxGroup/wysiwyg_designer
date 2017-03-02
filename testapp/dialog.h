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
    ~Dialog();

private slots:
    void onChanged();
    void onAttrChanged(const QString &name, const QVariant &value);

private:
    Ui::Dialog *ui;

    WysiwygEditor editor;
};

#endif // DIALOG_H
