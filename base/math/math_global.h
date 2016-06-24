#ifndef MATH_GLOBAL_H
#define MATH_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef MATH_LIB
# define MATH_EXPORT Q_DECL_EXPORT
#else
# define MATH_EXPORT Q_DECL_IMPORT
#endif

#endif // MATH_GLOBAL_H