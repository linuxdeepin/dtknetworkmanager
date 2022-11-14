// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dactivevpnconnectioninterface.h"
#include <QDBusArgument>

DNETWORKMANAGER_BEGIN_NAMESPACE

DActiveVPNConnectionInterface::DActiveVPNConnectionInterface(const QByteArray &path, QObject *parent)
    : DActiveConnectionInterface(path, parent)
{
#ifdef USE_FAKE_INTERFACE
    const QString &Service = QStringLiteral("com.deepin.daemon.FakeNetworkManager");
    const QString &Interface = QStringLiteral("com.deepin.daemon.FakeNetworkManager.VPN.Connection");
    QDBusConnection Connection = QDBusConnection::sessionBus();
#else
    const QString &Service = QStringLiteral("org.freedesktop.NetworkManager");
    const QString &Interface = QStringLiteral("org.freedesktop.NetworkManager.VPN.Connection");
    QDBusConnection Connection = QDBusConnection::systemBus();
    Connection.connect(Service, path, Interface, "VpnStateChanged", this, SLOT([this](const quint32 state, const quint32 reason) {
                           emit this->VpnStateChanged(state, reason);
                       }));
#endif
    m_vpninter = new DDBusInterface(Service, path, Interface, Connection, this);
}

quint32 DActiveVPNConnectionInterface::vpnState() const
{
    return qdbus_cast<quint32>(m_vpninter->property("VpnState"));
};

QString DActiveVPNConnectionInterface::banner() const
{
    return qdbus_cast<QString>(m_vpninter->property("Banner"));
}

DNETWORKMANAGER_END_NAMESPACE
