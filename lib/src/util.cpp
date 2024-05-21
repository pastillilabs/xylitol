#include "xylitol/util.h"
#include "xylitol/logging.h"

#include "conversions.h"

#include <QBuffer>
#include <QImage>
#include <QMetaProperty>

namespace Xylitol {

QVariant toVariant(const QVariant& variant) {
    return Private::toVariant(variant);
}

QVariant fromVariant(const QVariant& variant, int metaTypeId, QObject* parent) {
    return Private::fromVariant(variant, metaTypeId, parent);
}

QVariant toVariant(const QObject& object) {
    return Private::toVariant(&object);
}

void fromVariant(QObject& object, const QVariant& variant) {
    Private::fromVariant(&object, variant);
}

QVariant toVariant(const void* gadget, const QMetaObject& metaObject) {
    return Private::toVariant(gadget, metaObject);
}

void fromVariant(void* gadget, int metaTypeId, const QVariant& variant) {
    Private::fromVariant(gadget, metaTypeId, variant);
}

bool equals(const void* gadget, const void* other, const QMetaObject& metaObject) {
    bool result = false;

    if(gadget != nullptr && other != nullptr) {
        result = true;

        const int propertyCount = metaObject.propertyCount();
        int propertyOffset = metaObject.propertyOffset();
        while((propertyOffset < propertyCount) && result) {
            const QMetaProperty metaProperty = metaObject.property(propertyOffset);

            const QVariant first = metaProperty.readOnGadget(gadget);
            const QVariant second = metaProperty.readOnGadget(other);

            result = (first == second);
            ++propertyOffset;
        }
    }
    else {
        qCWarning(category) << "Invalid parameters";
    }

    return result;
}

QVariant property(const QVariantMap& variantMap, const QString& name) {
    return variantMap.value(QLatin1String("properties")).toMap().value(name);
}

} // namespace Xylitol
