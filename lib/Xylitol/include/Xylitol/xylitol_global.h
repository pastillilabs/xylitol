#pragma once

#include <QtCore/qglobal.h>

#if defined(XYLITOL_LIBRARY)
#    define XYLITOL_SHARED_EXPORT Q_DECL_EXPORT
#else
#    define XYLITOL_SHARED_EXPORT Q_DECL_IMPORT
#endif
