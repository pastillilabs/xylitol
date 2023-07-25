#include "gadget.h"

#include <xylitol/util.h>

#include <QJsonObject>

Gadget::Gadget(int a, const QString& b, qint64 c, const QJsonObject& d)
    : mA(a)
    , mB(b)
    , mC(c)
    , mD(d) {}

bool Gadget::operator==(const Gadget& other) const {
    return Xylitol::equals(this, reinterpret_cast<const void*>(&other), staticMetaObject);
}

bool Gadget::operator!=(const Gadget& other) const {
    return !Xylitol::equals(this, reinterpret_cast<const void*>(&other), staticMetaObject);
}

bool Gadget::operator<(const Gadget& /*other*/) const {
    return false;
}
