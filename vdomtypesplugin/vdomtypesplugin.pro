#-------------------------------------------------
#
# Project created by QtCreator 2017-02-13T16:02:53
#
#-------------------------------------------------

CONFIG += designer plugin

QT += webkit network svg

TARGET = vdomtypesplugin
TEMPLATE = lib

DEFINES += VDOMTYPESPLUGIN_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ../common $(QTDIR)/tools/designer/src/lib/shared

SOURCES += vdomtypesplugin.cpp \
    vdompluginextension.cpp \
    vdomtypeswidget.cpp \
    ../common/typesloader.cpp \
    ../common/path.cpp \
    vdomclassfactory.cpp \
    ../common/util.cpp \
    ../common/protocol.cpp \
    listener.cpp \
    ../common/wysiwyg.cpp

HEADERS += vdomtypesplugin.h\
        vdomtypesplugin_global.h \
    vdompluginextension.h \
    vdomtypeswidget.h \
    ../common/typesloader.h \
    ../common/path.h \
    vdomclassfactory.h \
    vdomclasses.h \
    ../common/util.h \
    ../common/protocol.h \
    listener.h \
    ../common/wysiwyg.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
