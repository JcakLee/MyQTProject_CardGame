# 基础数据库项目
QT += core gui
TEMPLATE = lib
CONFIG += dynamiclib
include(../common.pri)

# 项目特定配置
TARGET = BaseData
DEFINES += BaseData_LIBRARY

# 源文件
HEADERS += \
    *.h \

SOURCES += \
    *.cpp \

# 安装配置
target.path = $$DESTDIR
INSTALLS += target

# 调试信息
message("[BaseData] 目标文件: $$TARGET")
message("[BaseData] 输出到: $$DESTDIR")
