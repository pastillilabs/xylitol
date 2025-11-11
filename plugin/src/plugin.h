#pragma once

#include <QQmlExtensionPlugin>

/**
 * @brief The Plugin class
 */
class Plugin : public QQmlExtensionPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public: // From QQmlExtensionPlugin
    void registerTypes(const char* uri) override;
};
