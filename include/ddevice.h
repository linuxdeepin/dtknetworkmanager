// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DDEVICE_H
#define DDEVICE_H

#include "dnetworkmanagertypes.h"
#include <DExpected>

DNETWORKMANAGER_BEGIN_NAMESPACE

class DDevicePrivate;

using DCORE_NAMESPACE::DExpected;

class DDevice : public QObject
{
    Q_OBJECT
public:
    explicit DDevice(const quint64 deviceId, QObject *parent = nullptr);
    ~DDevice() = default;

    Q_PROPERTY(QList<quint64> availableConnections READ availableConnections NOTIFY availableConnectionsChanged)
    Q_PROPERTY(bool autoconnect READ autoconnect WRITE setAutoconnect NOTIFY autoconnectChanged)
    Q_PROPERTY(bool managed READ managed WRITE setManaged NOTIFY managedChanged)
    Q_PROPERTY(quint64 activeConnection READ activeConnection NOTIFY activeConnectionChanged)
    Q_PROPERTY(quint64 DHCP4Config READ DHCP4Config NOTIFY DHCP4ConfigChanged)
    Q_PROPERTY(quint64 DHCP6Config READ DHCP6Config NOTIFY DHCP4ConfigChanged)
    Q_PROPERTY(quint64 IPv4Config READ IPv4Config NOTIFY IPv4ConfigChanged)
    Q_PROPERTY(quint64 IPv6Config READ IPv6Config NOTIFY IPv6ConfigChanged)
    Q_PROPERTY(QByteArray driver READ driver NOTIFY driverChanged)
    Q_PROPERTY(QByteArray interface READ interface NOTIFY interfaceChanged)
    Q_PROPERTY(QByteArray udi READ udi NOTIFY udiChanged)
    Q_PROPERTY(NMDeviceType deviceType READ deviceType NOTIFY deviceTypeChanged)
    Q_PROPERTY(NMDeviceInterfaceFlags interfaceFlags READ interfaceFlags NOTIFY interfaceFlagsChanged)
    Q_PROPERTY(NMDeviceState deviceState READ deviceState NOTIFY deviceStateChanged)
    Q_PROPERTY(quint32 refreshRateMs READ refreshRateMs WRITE setRefreshRateMs NOTIFY refreshRateMsChanged)
    Q_PROPERTY(quint32 rxBytes READ rxBytes NOTIFY rxBytesChanged)
    Q_PROPERTY(quint32 txBytes READ txBytes NOTIFY txBytesChanged)

    QList<quint64> availableConnections() const;
    bool autoconnect() const;
    void setAutoconnect(const bool autoconnect) const;
    bool managed() const;
    void setManaged(const bool managed) const;
    quint64 activeConnection() const;
    quint64 DHCP4Config() const;
    quint64 DHCP6Config() const;
    quint64 IPv4Config() const;
    quint64 IPv6Config() const;
    QByteArray driver() const;
    QByteArray interface() const;
    QByteArray udi() const;
    NMDeviceType deviceType() const;
    NMDeviceInterfaceFlags interfaceFlags() const;
    NMDeviceState deviceState() const;
    quint32 refreshRateMs() const;
    void setRefreshRateMs(const quint32 newRate) const;
    quint32 rxBytes() const;
    quint32 txBytes() const;

public slots:
    DExpected<void> disconnect() const;

signals:
    void deviceStateChanged(const NMDeviceState newSatate, const NMDeviceState oldState, const NMDeviceStateReason reason);
    void availableConnectionsChanged(const QList<quint64> &conns);
    void autoconnectChanged(const bool enabled);
    void managedChanged(const bool enabled);
    void activeConnectionChanged(const quint64 &conn);
    void DHCP4ConfigChanged(const quint64 &config);
    void DHCP6ConfigChanged(const quint64 &config);
    void IPv4ConfigChanged(const quint64 &config);
    void IPv6ConfigChanged(const quint64 &config);
    void driverChanged(const QByteArray &driver);
    void interfaceChanged(const QByteArray &ifc);
    void udiChanged(const QByteArray &udi);
    void deviceTypeChanged(const NMDeviceType type);
    void interfaceFlagsChanged(const NMDeviceInterfaceFlags flags);
    void refreshRateMsChanged(const quint32 rate);
    void rxBytesChanged(const quint32 bytes);
    void txBytesChanged(const quint32 bytes);

private:
    QScopedPointer<DDevicePrivate> d_ptr;
    Q_DECLARE_PRIVATE(DDevice)
};

DNETWORKMANAGER_END_NAMESPACE

#endif
