#-------------------------------------------------
#
# Project created by QtCreator 2017-02-13T16:06:47
#
#-------------------------------------------------

QT       += core gui widgets network

TARGET = wysiwygeditor
TEMPLATE = lib
CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ../designerlib ../common $(QTDIR)/tools/designer/src/lib/shared ../../vdom/include

SOURCES += wysiwygeditor.cpp \
    ../common/typesloader.cpp \
    widgetsfile.cpp \
    ../common/path.cpp \
    converter.cpp \
    ../common/util.cpp \
    ../common/protocol.cpp \
    localsocketclient.cpp \
    ../common/vdomxml.cpp

HEADERS += wysiwygeditor.h \
    ../common/typesloader.h \
    widgetsfile.h \
    ../common/path.h \
    converter.h \
    ../common/util.h \
    ../common/protocol.h \
    localsocketclient.h \
    ../common/vdomxml.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
