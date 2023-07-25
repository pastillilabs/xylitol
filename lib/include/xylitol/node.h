#pragma once

#include <xylitol/connection.h>
#include <xylitol/socket.h>
#include <xylitol/xylitol_global.h>

#include <QAbstractListModel>
#include <QObject>
#include <QVariant>
#include <QVariantList>
#include <QVector>

namespace Xylitol {

class ShadowObject;

/**
 * @brief The Node class
 */
class XYLITOL_EXPORT Node : public QAbstractListModel {
    Q_OBJECT
#if QT_VERSION < QT_VERSION_CHECK(5, 15, 0)
    Q_PROPERTY(QObject* target READ target WRITE setTarget NOTIFY targetChanged)
#else
    Q_PROPERTY(QObject* target READ target WRITE setTarget NOTIFY targetChanged REQUIRED)
#endif
    Q_PROPERTY(bool initialized READ isInitialized NOTIFY initializedChanged)
    Q_PROPERTY(Connection* parentConnection READ parentConnection NOTIFY parentConnectionChanged)
    Q_PROPERTY(Connection* activeConnection READ activeConnection NOTIFY activeConnectionChanged)

    Q_CLASSINFO("DefaultProperty", "target")

public:
    explicit Node(QObject* parent = nullptr);

    QObject* target() const;
    void setTarget(QObject* target);

    bool isInitialized() const;

    Connection* parentConnection() const;
    const QVector<Connection*>& childConnectionContainer() const;
    Connection* activeConnection() const;

    Q_INVOKABLE void setParentSocket(Xylitol::Socket* socket);
    Q_INVOKABLE void addChildSocket(Xylitol::Socket* socket);
    Q_INVOKABLE void removeChildSocket(Xylitol::Socket* socket);

public: // From QAbstractListModel
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

private:
    void setInitialized(bool initialized);
    void setupConnection(Connection& connection);

    void sendAll(Socket::Action action, const QVariantList& path, const QVariant& data, Connection* source = nullptr);

signals:
    void targetChanged(QObject* target);
    void parentSocketChanged(Xylitol::Socket* parentSocket);
    void initializedChanged(bool initialized);
    void parentConnectionChanged(Xylitol::Connection* parentConnection);
    void activeConnectionChanged(Xylitol::Connection* activeConnection);

private slots:
    void invoked(const QVariantList& path, const QVariantList& values);
    void updated(const QVariantList& path, const QVariant& value);

private:
    QObject* mTarget{nullptr};
    ShadowObject* mTargetShadow{nullptr};

    bool mInitialized{true};

    Connection* mParentConnection{nullptr};
    QVector<Connection*> mChildConnections;
    Connection* mActiveConnection{nullptr};
};

} // namespace Xylitol
