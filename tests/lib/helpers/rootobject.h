#pragma once

#include "gadget.h"
#include "stringlistmodel.h"
#include "object.h"

/**
 * @brief The RootObject class
 */
class RootObject : public Object {
    Q_OBJECT
    Q_PROPERTY(StringListModel* stringListModel READ stringListModel CONSTANT)
    Q_PROPERTY(Object* childA READ childA CONSTANT)
    Q_PROPERTY(Object* childB READ childB CONSTANT)

    Q_PROPERTY(Gadget gadget READ gadget WRITE setGadget NOTIFY gadgetChanged)
    Q_PROPERTY(Gadget* gadgetPtr READ gadgetPtr WRITE setGadgetPtr NOTIFY gadgetPtrChanged)

public:
    explicit RootObject(QObject* parent = nullptr);

    StringListModel* stringListModel() const;
    Object* childA() const;
    Object* childB() const;

    const Gadget& gadget() const;
    void setGadget(const Gadget& gadget);

    Gadget* gadgetPtr() const;
    void setGadgetPtr(Gadget* gadgetPtr);

signals:
    void gadgetChanged(const Gadget& gadget);
    void gadgetPtrChanged(Gadget* gadgetPtr);

    // Non-property signals
    void testEmpty();
    void testGadget(const Gadget& gadget);

private:
    StringListModel* mStringListModel{nullptr};
    Object* mChildA{nullptr};
    Object* mChildB{nullptr};

    Gadget mGadget;
    Gadget* mGadgetPtr{nullptr};
};
