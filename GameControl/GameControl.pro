QT += core gui
TEMPLATE = lib
CONFIG += dynamiclib
include(../common.pri)

TARGET = GameControl
DEFINES += GameControl_LIBRARY
DEPENDPATH += $$PWD/../BaseData
INCLUDEPATH += $$PWD/../BaseData

CONFIG(debug, debug|release) {
    LIBS +=  \
         -lBaseData \
} else {
    LIBS +=  \
         -lBaseData \
}

HEADERS += \
    *.h \

SOURCES += \
    *.cpp \

RESOURCES += res.qrc

