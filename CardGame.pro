# 解决方案主文件
TEMPLATE = subdirs
CONFIG += ordered

# 包含全局配置
include(common.pri)

# 子项目定义（注意顺序）
SUBDIRS += \
    BaseData \
    GameControl \
    Pannel \
    CardGameApp \

RESOURCES += res.qrc

# 打印全局配置
message("[全局] 输出目录: $$DESTDIR")
message("[全局] 库搜索路径: $$LIBS")
