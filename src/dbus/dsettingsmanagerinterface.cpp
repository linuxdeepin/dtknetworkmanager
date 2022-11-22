// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dsettingsmanagerinterface.h"

DNETWORKMANAGER_BEGIN_NAMESPACE

DSettingsManagerInterface::DSettingsManagerInterface(QObject *parent)
    : QObject(parent)
{
#ifdef USE_FAKE_INTERFACE
    const QString &Service = QStringLiteral("com.deepin.daemon.FakeNetworkManager");
    const QString &Interface = QStringLiteral("com.deepin.daemon.FakeNetworkManager.Settings");
    const QString &Path = QStringLiteral("/com/deepin/daemon/FakeNetworkManager/Settings");
    QDBusConnection Connection = QDBusConnection::sessionBus();
#else
    const QString &Service = QStringLiteral("org.freedesktop.NetworkManager");
    const QString &Interface = QStringLiteral("org.freedesktop.NetworkManager.Settings");
    const QString &Path = QStringLiteral("/org/freedesktop/NetworkManager/Settings");
    QDBusConnection Connection = QDBusConnection::systemBus();
    Connection.connect(Service, Path, Interface, "ConnectionRemoved", this, SLOT([this](const QDBusObjectPath &parh) {
                           emit this->ConnectionRemoved(path);
                       }));
    Connection.connect(Service, Path, Interface, "NewConnection", this, SLOT([this](const QDBusObjectPath &path) {
                           emit this->NewConnection(path);
                       }));
#endif
    m_inter = new DDBusInterface(Service, Path, Interface, Connection, this);
}

QDBusPendingReply<QList<QDBusObjectPath>> DSettingsManagerInterface::listConnections() const
{
    return m_inter->asyncCall("ListConnections");
}

QDBusPendingReply<QDBusObjectPath> DSettingsManagerInterface::getConnectionByUUID(const QByteArray &UUID) const
{
    return m_inter->asyncCallWithArgumentList("GetConnectionByUuid", {QVariant::fromValue(QString(UUID))});
}

QDBusPendingReply<QDBusObjectPath> DSettingsManagerInterface::addConnection(const SettingDesc &conn) const
{
    return m_inter->asyncCallWithArgumentList("AddConnection", {QVariant::fromValue(conn)});
}

DNETWORKMANAGER_END_NAMESPACE
