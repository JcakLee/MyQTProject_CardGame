# 主应用程序
TEMPLATE = app
include(../common.pri)

# 项目特定配置
TARGET = CardGame
DEFINES += QT_DEPRECATED_WARNINGS

# 依赖配置 - 按正确顺序！
LIBS += \
    -L$$DESTDIR \
    -lBaseData \
    -lGameControl \    # 添加缺失的依赖
    -lPannel

DEPENDPATH += \
    $$PWD/../BaseData \
    $$PWD/../GameControl \  # 添加缺失的路径
    $$PWD/../Pannel

INCLUDEPATH += \
    $$PWD/../BaseData \
    $$PWD/../GameControl \  # 添加缺失的路径
    $$PWD/../Pannel

# 明确列出源文件（避免通配符问题）
SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# 翻译文件
TRANSLATIONS += CardGame_zh_CN.ts
CONFIG += lrelease embed_translations

RESOURCES += \
   $$PWD/../res.qrc \

# 调试信息
message("[App] 最终链接库: $$LIBS")
message("[App] 包含路径: $$INCLUDEPATH")
