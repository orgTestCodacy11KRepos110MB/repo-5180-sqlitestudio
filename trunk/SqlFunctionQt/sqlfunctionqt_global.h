#ifndef SQLFUNCTIONQT_GLOBAL_H
#define SQLFUNCTIONQT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SQLFUNCTIONQT_LIBRARY)
#  define SQLFUNCTIONQTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SQLFUNCTIONQTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SQLFUNCTIONQT_GLOBAL_H
