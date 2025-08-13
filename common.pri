# 全局共享配置
#--------------------------------------------------
# 输出目录配置
#--------------------------------------------------
CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/output/debug
    CONFIG += debug
    message("[配置] Debug模式输出目录: $$DESTDIR")
} else {
    DESTDIR = $$PWD/output/release
    message("[配置] Release模式输出目录: $$DESTDIR")
}

# 确保目录存在
!exists($$DESTDIR) {
    mkpath($$DESTDIR)
    message("[系统] 创建目录: $$DESTDIR")
}

# 基础库链接配置
LIBS += -L$$DESTDIR
DEPENDPATH += $$DESTDIR

# Qt模块配置
QT += core gui widgets

# 编译选项
CONFIG += c++17 warn_on
CONFIG -= qt_quick

# 打印最终配置
message("[最终] 库搜索路径: $$LIBS")
