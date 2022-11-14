// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dipconflictcheckinterface.h"

DNETWORKMANAGER_BEGIN_NAMESPACE

DIPConflictCheckInterface::DIPConflictCheckInterface(QObject *parent)
    : QObject(parent)
{
#ifdef USE_FAKE_INTERFACE
    const QString &Service = QStringLiteral("com.deepin.daemon.FakeNetworkManager");
    const QString &Interface = QStringLiteral("com.deepin.daemon.FakeNetworkManager.IPWatchD");
    const QString &Path = QStringLiteral("/com/deepin/daemon/FakeNetworkManager/IPWatchD");
    QDBusConnection Connection = QDBusConnection::sessionBus();
#else
    const QString &Service = QStringLiteral("com.deepin.system.IPWatchD");
    const QString &Interface = QStringLiteral("com.deepin.system.IPWatchD");
    const QString &Path = QStringLiteral("/com/deepin/system/IPWatchD");
    QDBusConnection Connection = QDBusConnection::systemBus();
    Connection.connect(
        Service, Path, Interface, "IPConflict", this, SLOT([this](const QString &ip, const QString &smac, const QString &dmac) {
            emit this->IPConflict(ip, smac, dmac);
        }));
#endif
    m_inter = new DDBusInterface(Service, Path, Interface, Connection, this);
}

QDBusPendingReply<QString> DIPConflictCheckInterface::requestIPConflictCheck(const QByteArray &ip, const QByteArray &ifc) const
{
    return m_inter->asyncCallWithArgumentList("RequestIPConflictCheck",
                                              {QVariant::fromValue(QString(ip)), QVariant::fromValue(QString(ifc))});
}

DNETWORKMANAGER_END_NAMESPACE
