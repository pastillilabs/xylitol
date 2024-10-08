#pragma once

#include <xylitol/xylitol_global.h>

#include <QMetaObject>
#include <QObject>
#include <QVariant>
#include <QVariantMap>

namespace Xylitol {

XYLITOL_SHARED_EXPORT QVariant toVariant(const QVariant& variant);
XYLITOL_SHARED_EXPORT QVariant fromVariant(const QVariant& variant, int metaTypeId, QObject* parent = nullptr);

XYLITOL_SHARED_EXPORT QVariant toVariant(const QObject& object);
XYLITOL_SHARED_EXPORT void fromVariant(QObject& object, const QVariant& variant);

XYLITOL_SHARED_EXPORT QVariant toVariant(const void* gadget, const QMetaObject& metaObject);
XYLITOL_SHARED_EXPORT void fromVariant(void* gadget, int metaTypeId, const QVariant& variant);

XYLITOL_SHARED_EXPORT bool equals(const void* gadget, const void* other, const QMetaObject& metaObject);
XYLITOL_SHARED_EXPORT QVariant property(const QVariantMap& variantMap, const QString& name);

} // namespace Xylitol
