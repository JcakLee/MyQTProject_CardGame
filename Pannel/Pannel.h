#ifndef _PANNEL_H
#define _PANNEL_H

#include <QtCore/qglobal.h>  // 引入 Qt 的宏定义

#if defined(Pannel_LIBRARY)
#define EXPORT_PANNEL_ABI Q_DECL_EXPORT
#else
#define EXPORT_PANNEL_ABI Q_DECL_IMPORT
#endif

#endif // PANNEL_H
