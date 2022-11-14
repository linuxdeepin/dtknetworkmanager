// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dagentmanagerinterface.h"

DNETWORKMANAGER_BEGIN_NAMESPACE

DAgentManagerInterface::DAgentManagerInterface(QObject *parent)
    : QObject(parent)
{
#ifdef USE_FAKE_INTERFACE
    const QString &Service = QStringLiteral("com.deepin.daemon.FakeNetworkManager");
    const QString &Interface = QStringLiteral("com.deepin.daemon.FakeNetworkManager.AgentManager");
    const QString &Path = QStringLiteral("/com/deepin/daemon/FakeNetworkManager/AgentManager");
    QDBusConnection Connection = QDBusConnection::sessionBus();
#else
    const QString &Service = QStringLiteral("org.freedesktop.NetworkManager");
    const QString &Interface = QStringLiteral("org.freedesktop.NetworkManager.AgentManager");
    const QString &Path = QStringLiteral("/org/freedesktop/NetworkManager/AgentManager");
    QDBusConnection Connection = QDBusConnection::systemBus();
#endif
    m_inter = new DDBusInterface(Service, Path, Interface, Connection, this);
}

QDBusPendingReply<void> DAgentManagerInterface::registerAgent(const QByteArray &identifier) const
{
    return m_inter->asyncCallWithArgumentList("Register", {QVariant::fromValue(identifier)});
}

QDBusPendingReply<void> DAgentManagerInterface::registerWithCapabilities(const QByteArray &identifier,
                                                                         const NMSecretAgentCapabilities cap) const
{
    return m_inter->asyncCallWithArgumentList("RegisterWithCapabilities",
                                              {QVariant::fromValue(identifier), QVariant::fromValue(static_cast<quint32>(cap))});
}

QDBusPendingReply<void> DAgentManagerInterface::unregisterAgent() const
{
    return m_inter->asyncCall("Unregister");
}

DNETWORKMANAGER_END_NAMESPACE
