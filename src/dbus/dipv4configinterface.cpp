// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dipv4configinterface.h"
#include <QDBusArgument>

DNETWORKMANAGER_BEGIN_NAMESPACE

DIPv4ConfigInterface::DIPv4ConfigInterface(const QByteArray &path, QObject *parent)
    : QObject(parent)
{
#ifdef USE_FAKE_INTERFACE
    const QString &Service = QStringLiteral("com.deepin.daemon.FakeNetworkManager");
    const QString &Interface = QStringLiteral("com.deepin.daemon.FakeNetworkManager.IP4Config");
    QDBusConnection Connection = QDBusConnection::sessionBus();
#else
    const QString &Service = QStringLiteral("org.freedesktop.NetworkManager");
    const QString &Interface = QStringLiteral("org.freedesktop.NetworkManager.IP4Config");
    QDBusConnection Connection = QDBusConnection::systemBus();
#endif
    m_inter = new DDBusInterface(Service, path, Interface, Connection, this);
}

QList<Config> DIPv4ConfigInterface::addressData() const
{
    return qdbus_cast<QList<Config>>(m_inter->property("AddressData"));
}

QList<Config> DIPv4ConfigInterface::nameserverData() const
{
    return qdbus_cast<QList<Config>>(m_inter->property("NameserverData"));
}

QString DIPv4ConfigInterface::gateway() const
{
    return qdbus_cast<QString>(m_inter->property("Gateway"));
}

DNETWORKMANAGER_END_NAMESPACE
