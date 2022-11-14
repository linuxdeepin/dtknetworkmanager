// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DDEVICEINTERFACE_H
#define DDEVICEINTERFACE_H

#include "dnetworkmanager_global.h"
#include "dnetworkmanagertypes.h"
#include <DDBusInterface>
#include <QSharedPointer>
#include <QDBusPendingReply>
#include <QString>
#include <QMap>
#include <QVariant>
#include <QList>

DNETWORKMANAGER_BEGIN_NAMESPACE

using DTK_CORE_NAMESPACE::DDBusInterface;

class DDeviceInterface : public QObject
{
    Q_OBJECT
public:
    explicit DDeviceInterface(const QByteArray &path, QObject *parent = nullptr);
    ~DDeviceInterface() = default;

    Q_PROPERTY(QList<QDBusObjectPath> availableConnections READ availableConnections NOTIFY availableConnectionsChanged)
    Q_PROPERTY(bool autoconnect READ autoconnect WRITE setAutoconnect NOTIFY autoconnectChanged)
    Q_PROPERTY(bool managed READ managed WRITE setManaged NOTIFY managedChanged)
    Q_PROPERTY(QDBusObjectPath activeConnection READ activeConnection NOTIFY activeConnectionChanged)
    Q_PROPERTY(QDBusObjectPath DHCP4Config READ DHCP4Config NOTIFY DHCP4ConfigChanged)
    Q_PROPERTY(QDBusObjectPath DHCP6Config READ DHCP6Config NOTIFY DHCP4ConfigChanged)
    Q_PROPERTY(QDBusObjectPath IPv4Config READ IPv4Config NOTIFY IPv4ConfigChanged)
    Q_PROPERTY(QDBusObjectPath IPv6Config READ IPv6Config NOTIFY IPv6ConfigChanged)
    Q_PROPERTY(QString driver READ driver NOTIFY driverChanged)
    Q_PROPERTY(QString interface READ interface NOTIFY interfaceChanged)
    Q_PROPERTY(QString udi READ udi NOTIFY udiChanged)
    Q_PROPERTY(quint32 deviceType READ deviceType NOTIFY deviceTypeChanged)
    Q_PROPERTY(quint32 interfaceFlags READ interfaceFlags NOTIFY interfaceFlagsChanged)
    Q_PROPERTY(quint32 state READ state NOTIFY stateChanged)
    Q_PROPERTY(quint32 refreshRateMs READ refreshRateMs WRITE setRefreshRateMs NOTIFY refreshRateMsChanged)
    Q_PROPERTY(quint32 rxBytes READ rxBytes NOTIFY rxBytesChanged)
    Q_PROPERTY(quint32 txBytes READ txBytes NOTIFY txBytesChanged)

    QList<QDBusObjectPath> availableConnections() const;
    bool autoconnect() const;
    void setAutoconnect(const bool autoconnect) const;
    bool managed() const;
    void setManaged(const bool managed) const;
    QDBusObjectPath activeConnection() const;
    QDBusObjectPath DHCP4Config() const;
    QDBusObjectPath DHCP6Config() const;
    QDBusObjectPath IPv4Config() const;
    QDBusObjectPath IPv6Config() const;
    QString driver() const;
    QString interface() const;
    QString udi() const;
    quint32 deviceType() const;
    quint32 interfaceFlags() const;
    quint32 state() const;
    quint32 refreshRateMs() const;
    void setRefreshRateMs(const quint32 newRate) const;
    quint32 rxBytes() const;
    quint32 txBytes() const;

public slots:

    QDBusPendingReply<void> disconnect() const;

signals:
    void StateChanged(const quint32 newSatate, const quint32 oldState, const quint32 reason);
    void availableConnectionsChanged(const QList<QDBusObjectPath> &conns);
    void autoconnectChanged(const bool enabled);
    void managedChanged(const bool enabled);
    void activeConnectionChanged(const QDBusObjectPath &conn);
    void DHCP4ConfigChanged(const QDBusObjectPath &config);
    void DHCP6ConfigChanged(const QDBusObjectPath &config);
    void IPv4ConfigChanged(const QDBusObjectPath &config);
    void IPv6ConfigChanged(const QDBusObjectPath &config);
    void driverChanged(const QString &driver);
    void interfaceChanged(const QString &ifc);
    void udiChanged(const QString &udi);
    void deviceTypeChanged(const quint32 type);
    void interfaceFlagsChanged(const quint32 flags);
    void stateChanged(const quint32 state);
    void refreshRateMsChanged(const quint32 rate);
    void rxBytesChanged(const quint32 bytes);
    void txBytesChanged(const quint32 bytes);

private:
    DDBusInterface *m_deviceInter{nullptr};
    DDBusInterface *m_statisticsInter{nullptr};
};

DNETWORKMANAGER_END_NAMESPACE

#endif
