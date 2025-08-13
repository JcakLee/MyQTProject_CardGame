#ifndef _BASEDATA_H
#define _BASEDATA_H

#include <QtCore/qglobal.h>  // 引入 Qt 的宏定义

#if defined(BaseData_LIBRARY)
#define EXPORT_BASEDATA_ABI Q_DECL_EXPORT
#else
#define EXPORT_BASEDATA_ABI Q_DECL_IMPORT
#endif

#endif // _BASEDATA_H
