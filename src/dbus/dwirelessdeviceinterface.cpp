// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dwirelessdeviceinterface.h"

DNETWORKMANAGER_BEGIN_NAMESPACE

DWirelessDeviceInterface::DWirelessDeviceInterface(const QByteArray &path, QObject *parent)
    : DDeviceInterface(path, parent)
{
#ifdef USE_FAKE_INTERFACE
    const QString &Service = QStringLiteral("com.deepin.daemon.FakeNetworkManager");
    const QString &Interface = QStringLiteral("com.deepin.daemon.FakeNetworkManager.Device.Wireless");
    QDBusConnection Connection = QDBusConnection::sessionBus();
#else
    const QString &Service = QStringLiteral("org.freedesktop.NetworkManager");
    const QString &Interface = QStringLiteral("org.freedesktop.NetworkManager.Device.Wireless");
    QDBusConnection Connection = QDBusConnection::systemBus();
    Connection.connect(Service, path, Interface, "AccessPointAdded", this, SLOT([this](const QDBusObjectPath &ap) {
                           emit this->AccessPointAdded(ap);
                       }));
    Connection.connect(Service, path, Interface, "AccessPointRemoved", this, SLOT([this](const QDBusObjectPath &ap) {
                           emit this->AccessPointRemoved(ap);
                       }));
#endif
    m_wirelessInter = new DDBusInterface(Service, path, Interface, Connection, this);
}

QDBusPendingReply<void> DWirelessDeviceInterface::requestScan(const Config &options) const
{
    return m_wirelessInter->asyncCallWithArgumentList("RequestScan", {QVariant::fromValue(options)});
}

QDBusPendingReply<QList<QDBusObjectPath>> DWirelessDeviceInterface::getAllAccessPoints() const
{
    return m_wirelessInter->asyncCall("GetAllAccessPoints");
}

DNETWORKMANAGER_END_NAMESPACE
