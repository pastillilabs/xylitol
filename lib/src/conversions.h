#pragma once

#include <QByteArray>
#include <QObject>
#include <QVariant>
#include <QVariantMap>

namespace Xylitol {
namespace Private {

bool canConvertToByteArray(const QVariant& variant);

QByteArray toByteArray(const QVariant& variant);
QVariant fromByteArray(const QByteArray& byteArray, int metaTypeId);

QVariant toVariant(const QVariant& variant);
QVariant fromVariant(const QVariant& variant, int metaTypeId, QObject* parent = nullptr);

QVariant toVariant(const QObject* object);
QVariant fromVariant(QObject* object, const QVariant& variant, int metaTypeId = 0, QObject* parent = nullptr);

QVariant toVariant(const void* gadget, const QMetaObject& metaObject);
QVariant fromVariant(void* gadget, int metaTypeId, const QVariant& variant);

void writeObjectProperty(QObject& object, const QMetaProperty& metaProperty, const QVariant& variant);
void writeObjectProperty(QObject& object, const QMetaProperty& metaProperty, const QByteArray& byteArray);

} // namespace Private
} // namespace Xylitol
