#include "rootobject.h"

RootObject::RootObject(QObject* parent)
    : Object(parent)
    , mStringListModel(new StringListModel(this))
    , mChildA(new Object(this))
    , mChildB(new Object(this)) {}

StringListModel* RootObject::stringListModel() const {
    return mStringListModel;
}

Object* RootObject::childA() const {
    return mChildA;
}

Object* RootObject::childB() const {
    return mChildB;
}

const Gadget& RootObject::gadget() const {
    return mGadget;
}

void RootObject::setGadget(const Gadget& gadget) {
    if(gadget != mGadget) {
        mGadget = gadget;
        emit gadgetChanged(gadget);
    }
}

Gadget* RootObject::gadgetPtr() const {
    return mGadgetPtr;
}

void RootObject::setGadgetPtr(Gadget* gadgetPtr) {
    if(gadgetPtr != mGadgetPtr) {
        mGadgetPtr = gadgetPtr;
        emit gadgetPtrChanged(gadgetPtr);
    }
}
