#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
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

private:
    Ui::Dialog *ui;

    WysiwygEditor editor;
};

#endif // DIALOG_H
