#pragma once

#include <Xylitol/xylitol_global.h>

#include <QLoggingCategory>

namespace Xylitol {

#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
Q_DECLARE_EXPORTED_LOGGING_CATEGORY(category, XYLITOL_SHARED_EXPORT)
#else
Q_DECLARE_LOGGING_CATEGORY(category)
#endif

} // namespace Xylitol
