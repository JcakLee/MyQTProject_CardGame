#ifndef _GAMECONTROLEX_H
#define _GAMECONTROLEX_H

#include <QtCore/qglobal.h>  // 引入 Qt 的宏定义

#if defined(GameControl_LIBRARY)
#define EXPORT_GAMECONTROL_ABI Q_DECL_EXPORT
#else
#define EXPORT_GAMECONTROL_ABI Q_DECL_IMPORT
#endif

#endif // _GAMECONTROLEX_H
