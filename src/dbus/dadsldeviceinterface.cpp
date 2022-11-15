// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dadsldeviceinterface.h"

DNETWORKMANAGER_BEGIN_NAMESPACE

DAdslDeviceInterface::DAdslDeviceInterface(const QByteArray &path, QObject *parent)
    : DDeviceInterface(path, parent)
{
#ifdef USE_FAKE_INTERFACE
    const QString &Service = QStringLiteral("com.deepin.daemon.FakeNetworkManager");
    const QString &Interface = QStringLiteral("com.deepin.daemon.FakeNetworkManager.Device.Adsl");
    QDBusConnection Connection = QDBusConnection::sessionBus();
#else
    const QString &Service = QStringLiteral("org.freedesktop.NetworkManager");
    const QString &Interface = QStringLiteral("org.freedesktop.NetworkManager.Device.Adsl");
    QDBusConnection Connection = QDBusConnection::systemBus();
#endif
    m_adslInter = new DDBusInterface(Service, path, Interface, Connection, this);
}

bool DAdslDeviceInterface::carrier() const
{
    return qdbus_cast<bool>(m_adslInter->property("Carrier"));
}

DNETWORKMANAGER_END_NAMESPACE
