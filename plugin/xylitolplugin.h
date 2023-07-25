#pragma once

#include <QQmlExtensionPlugin>

/**
 * @brief The XylitolPlugin class
 */
class XylitolPlugin : public QQmlExtensionPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public: // From QQmlExtensionPlugin
    void registerTypes(const char* uri) override;
};
