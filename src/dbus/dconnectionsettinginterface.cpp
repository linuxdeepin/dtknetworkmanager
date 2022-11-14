// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dconnectionsettinginterface.h"
#include <QDBusArgument>

DNETWORKMANAGER_BEGIN_NAMESPACE

DConnectionSettingInterface::DConnectionSettingInterface(const QByteArray &path, QObject *parent)
    : QObject(parent)
{
#ifdef USE_FAKE_INTERFACE
    const QString &Service = QStringLiteral("com.deepin.daemon.FakeNetworkManager");
    const QString &Interface = QStringLiteral("com.deepin.daemon.FakeNetworkManager.Settings.Connection");
    QDBusConnection Connection = QDBusConnection::sessionBus();
#else
    const QString &Service = QStringLiteral("org.freedesktop.NetworkManager");
    const QString &Interface = QStringLiteral("org.freedesktop.NetworkManager.Settings.Connection");
    QDBusConnection Connection = QDBusConnection::systemBus();
    Connection.connect(Service, path, Interface, "Updated", this, SLOT([this]() { emit this->Updated(); }));
    Connection.connect(Service, path, Interface, "Removed", this, SLOT([this]() { emit this->Removed(); }));
#endif
    m_inter = new DDBusInterface(Service, path, Interface, Connection, this);
}

QDBusPendingReply<void> DConnectionSettingInterface::UpdateSetting(const SettingDesc &prop) const
{
    return m_inter->asyncCallWithArgumentList("Update", {QVariant::fromValue(prop)});
}

QDBusPendingReply<void> DConnectionSettingInterface::deleteSetting() const
{
    return m_inter->asyncCall("Delete");
}

QDBusPendingReply<SettingDesc> DConnectionSettingInterface::getSettigns() const
{
    return m_inter->asyncCall("GetSettings");
}

DNETWORKMANAGER_END_NAMESPACE
