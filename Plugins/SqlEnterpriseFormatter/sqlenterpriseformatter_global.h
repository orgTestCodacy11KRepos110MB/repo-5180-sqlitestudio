#ifndef SQLENTERPRISEFORMATTER_GLOBAL_H
#define SQLENTERPRISEFORMATTER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SQLENTERPRISEFORMATTER_LIBRARY)
#  define SQLENTERPRISEFORMATTERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SQLENTERPRISEFORMATTERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SQLENTERPRISEFORMATTER_GLOBAL_H