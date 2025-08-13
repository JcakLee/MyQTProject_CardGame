# 主应用程序
TEMPLATE = app
include(../common.pri)

# 项目特定配置
TARGET = CardGame
DEFINES += QT_DEPRECATED_WARNINGS

# 依赖配置
LIBS += \
    -lBaseData \
    -lPannel

DEPENDPATH += \
    $$PWD/../BaseData \
    $$PWD/../Pannel

INCLUDEPATH += \
    $$PWD/../BaseData \
    $$PWD/../Pannel

# 源文件
SOURCES += \
    *.cpp \

HEADERS += \
     *.h \

FORMS += \
    mainwindow.ui

# 翻译文件
TRANSLATIONS += CardGame_zh_CN.ts
CONFIG += lrelease embed_translations

# 调试信息
message("[App] 最终链接库: $$LIBS")
