#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    if (w.init()) {
        w.show();
        return a.exec();
    }
    return 0;
}
