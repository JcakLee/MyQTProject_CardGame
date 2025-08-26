# 面板库项目
QT += core gui widgets
TEMPLATE = lib
CONFIG += dynamiclib
include(../common.pri)

# 项目特定配置
TARGET = Pannel
DEFINES += Pannel_LIBRARY

# 依赖配置
LIBS += -lBaseData  # 链接BaseData库
DEPENDPATH += $$PWD/../BaseData
INCLUDEPATH += $$PWD/../BaseData

# 源文件
HEADERS += \
    *.h \

SOURCES += \
    *.cpp \

# 调试信息
message("[Pannel] 正在链接库: $$LIBS")

FORMS += \
    scorepannel.ui \
    buttongroup.ui \

RESOURCES += res.qrc
