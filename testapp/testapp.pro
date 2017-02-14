#-------------------------------------------------
#
# Project created by QtCreator 2017-02-13T16:10:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testapp
TEMPLATE = app

CONFIG += designer

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ../wysiwygeditor ../designerlib

SOURCES += main.cpp\
        dialog.cpp

HEADERS  += dialog.h

LIBS += -L../debug -lwysiwygeditor -ldesignerlib

FORMS    += dialog.ui

CONFIG(release, debug|release) {
    LIBS += -lQtDesignerComponents
}
CONFIG(debug, debug|release) {
    LIBS += -lQtDesignerComponentsd
}
