#-------------------------------------------------
#
# Project created by QtCreator 2017-02-13T15:52:00
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = designerlib
TEMPLATE = lib
CONFIG += staticlib designer

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += designer.cpp \
    designercore.cpp \
    integration/formresizer.cpp \
    integration/sizehandlerect.cpp \
    integration/widgethost.cpp

HEADERS += designer.h \
    designercommon.h \
    designercore.h \
    integration/formresizer.h \
    integration/namespace_global.h \
    integration/sizehandlerect.h \
    integration/widgethost.h \
    integration/widgethostconstants.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
