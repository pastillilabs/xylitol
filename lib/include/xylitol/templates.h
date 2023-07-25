#pragma once

#include <xylitol/util.h>

#include <QMetaType>
#include <QVariantList>
#include <QVariantMap>

namespace Xylitol {

template<class T>
QVariantList toVariantList(const T& container) {
    QVariantList variantList;
    for(const auto& item : container) {
        variantList.append(item);
    }

    return variantList;
};

template<class T>
T toContainer(const QVariantList& variantList) {
    T container;
    for(const auto& item : variantList) {
        container.append(item.value<typename T::value_type>());
    }

    return container;
};

template<class T>
class Gadget;

template<class T>
void registerGadget() {
    qRegisterMetaType<T>();

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    if(!QMetaType::hasRegisteredComparators<T>()) {
        QMetaType::registerComparators<T>();
    }
#endif

    // To QVariantMap conversion
    if(!QMetaType::hasRegisteredConverterFunction<T, QVariantMap>()) {
        const auto converter = [](const T& t) -> QVariantMap {
            return toVariant(&t, T::staticMetaObject).toMap();
        };

        QMetaType::registerConverter<T, QVariantMap>(converter);
    }

    // From QVariantMap conversion
    if(!QMetaType::hasRegisteredConverterFunction<QVariantMap, T>()) {
        const auto converter = [](const QVariantMap& variantMap) -> T {
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
            const int metaTypeId = T::staticMetaObject.metaType().id();
#else
            const int metaTypeId = QMetaType::type(T::staticMetaObject.className());
#endif

            T t;
            fromVariant(&t, metaTypeId, variantMap);
            return t;
        };

        QMetaType::registerConverter<QVariantMap, T>(converter);
    }

#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
    qRegisterMetaType<T*>();

    // To void* conversion
    if(!QMetaType::hasRegisteredConverterFunction<T*, void*>()) {
        const auto converter = [](T* t) -> void* {
            return reinterpret_cast<void*>(t);
        };

        QMetaType::registerConverter<T*, void*>(converter);
    }

    // From void* conversion
    if(!QMetaType::hasRegisteredConverterFunction<void*, T*>()) {
        const auto converter = [](void* v) -> T* {
            return reinterpret_cast<T*>(v);
        };

        QMetaType::registerConverter<void*, T*>(converter);
    }
#endif
}

template<typename T>
void registerContainer() {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    if(!QMetaType::hasRegisteredComparators<T>()) {
        QMetaType::registerComparators<T>();
    }
#endif

    // To QVariantList conversion
    if(!QMetaType::hasRegisteredConverterFunction<T, QVariantList>()) {
        QMetaType::registerConverter<T, QVariantList>(toVariantList<T>);
    }

    // From QVariantList conversion
    if(!QMetaType::hasRegisteredConverterFunction<QVariantList, T>()) {
        QMetaType::registerConverter<QVariantList, T>(toContainer<T>);
    }
}

} // namespace Xylitol
