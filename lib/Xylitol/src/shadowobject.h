#pragma once

#include "shadowobjectbase.h"

#include <QMap>
#include <QMetaProperty>

namespace Xylitol {

class AbstractListModel;

/**
 * @brief The ShadowObject class
 */
class ShadowObject : public ShadowObjectBase {
public:
    explicit ShadowObject(const QObject& target, QObject* parent = nullptr);

public: // From ShadowObjectBase
    int qt_metacall(QMetaObject::Call call, int id, void** argv) override;

private:
    void connectModel(const AbstractListModel& model);
    void connectObjectProperty(const QObject& object, const QString& name);

    void connectObjectValues(const AbstractListModel& model, int first, int last, const QVariantList& roles);
    void connectObjectValue(const AbstractListModel& model, const QObject& object, int role);

private:
    QMap<int, QMetaProperty> mPropertyMap;
};

} // namespace Xylitol
