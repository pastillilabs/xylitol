#pragma once

#include <QObject>
#include <QStringList>
#include <QVariant>
#include <QVariantList>

namespace Xylitol {

/**
 * @brief The ShadowObjectBase class
 */
class ShadowObjectBase : public QObject {
    Q_OBJECT

public:
    explicit ShadowObjectBase(QObject* parent = nullptr);

signals:
    void propertySink();
    void signalSink();

    void invoked(const QVariantList& path, const QVariantList& values);
    void updated(const QVariantList& path, const QVariant& value);
};

} // namespace Xylitol
