// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dnetworkmanager.h"
#include "dnetworkmanager_p.h"
#include "dnmutils.h"

DNETWORKMANAGER_BEGIN_NAMESPACE

using DCORE_NAMESPACE::DUnexpected;
using DCORE_NAMESPACE::emplace_tag;

DNetworkManagerPrivate::DNetworkManagerPrivate(DNetworkManager *parent)
    : q_ptr(parent)
    , m_manager(new DNetworkManagerInterface(this))
{
}

DNetworkManager::DNetworkManager(QObject *parent)
    : QObject(parent)
    , d_ptr(new DNetworkManagerPrivate(this))
{
    Q_D(const DNetworkManager);

    connect(d->m_manager, &DNetworkManagerInterface::networkingEnabledChanged, this, &DNetworkManager::networkingEnabledChanged);

    connect(d->m_manager, &DNetworkManagerInterface::wirelessEnabledChanged, this, &DNetworkManager::wirelessEnabledChanged);

    connect(d->m_manager,
            &DNetworkManagerInterface::wirelessHardwareEnabledChanged,
            this,
            &DNetworkManager::wirelessHardwareEnabledChanged);

    connect(d->m_manager, &DNetworkManagerInterface::activeConnectionsChanged, this, [this](const QList<QDBusObjectPath> &conn) {
        QList<quint64> ret;
        for (const auto &it : conn)
            ret.append(getIdFromObjectPath(it));
        emit this->activeConnectionsChanged(ret);
    });

    connect(d->m_manager, &DNetworkManagerInterface::primaryConnectionChanged, this, [this](const QDBusObjectPath &conn) {
        emit this->primaryConnectionChanged(getIdFromObjectPath(conn));
    });

    connect(d->m_manager, &DNetworkManagerInterface::primaryConnectionTypeChanged, this, [this](const QString &type) {
        emit this->primaryConnectionTypeChanged(type.toUtf8());
    });

    connect(d->m_manager, &DNetworkManagerInterface::connectivityChanged, this, [this](const quint32 con) {
        emit this->connectivityChanged(static_cast<NMConnectivityState>(con));
    });

    connect(d->m_manager, &DNetworkManagerInterface::DeviceAdded, this, [this](const QDBusObjectPath &device) {
        emit this->DeviceAdded(getIdFromObjectPath(device));
    });

    connect(d->m_manager, &DNetworkManagerInterface::DeviceRemoved, this, [this](const QDBusObjectPath &device) {
        emit this->DeviceRemoved(getIdFromObjectPath(device));
    });

    connect(d->m_manager, &DNetworkManagerInterface::CheckPermissions, this, &DNetworkManager::CheckPermissions);

    connect(d->m_manager, &DNetworkManagerInterface::StateChanged, this, [this](const quint32 state) {
        emit this->StateChanged(static_cast<NMState>(state));
    });
}

bool DNetworkManager::networkingEnabled() const
{
    Q_D(const DNetworkManager);
    return d->m_manager->networkingEnabled();
}

bool DNetworkManager::wirelessEnabled() const
{
    Q_D(const DNetworkManager);
    return d->m_manager->wirelessEnabled();
}

void DNetworkManager::setWirelessEnabled(const bool enable) const
{
    Q_D(const DNetworkManager);
    d->m_manager->setWirelessEnabled(enable);
}

bool DNetworkManager::wirelessHardwareEnabled() const
{
    Q_D(const DNetworkManager);
    return d->m_manager->wirelessHardwareEnabled();
}

QList<quint64> DNetworkManager::activeConnections() const
{
    Q_D(const DNetworkManager);
    QList<quint64> ret;
    for (const auto &conn : d->m_manager->activeConnections())
        ret.append(getIdFromObjectPath(conn));
    return ret;
}

quint64 DNetworkManager::primaryConnection() const
{
    Q_D(const DNetworkManager);
    return getIdFromObjectPath(d->m_manager->primaryConnection());
}

QByteArray DNetworkManager::primaryConnectionType() const
{
    Q_D(const DNetworkManager);
    return d->m_manager->primaryConnectionType().toUtf8();
}

NMState DNetworkManager::state() const
{
    Q_D(const DNetworkManager);
    return static_cast<NMState>(d->m_manager->state());
}

NMConnectivityState DNetworkManager::connectivity() const
{
    Q_D(const DNetworkManager);
    return static_cast<NMConnectivityState>(d->m_manager->connectivity());
}

DExpected<QList<quint64>> DNetworkManager::devices() const
{
    Q_D(const DNetworkManager);
    auto reply = d->m_manager->getDevices();
    reply.waitForFinished();
    if (!reply.isValid())
        return DUnexpected{emplace_tag::USE_EMPLACE, reply.error().type(), reply.error().message()};
    QList<quint64> ret;
    for (const auto &it : reply.value())
        ret.append(getIdFromObjectPath(it));
    return ret;
}

DExpected<quint64>
DNetworkManager::activateConnection(const quint64 connId, const quint64 &deviceId, const QByteArray specObj) const
{
    Q_D(const DNetworkManager);
    auto reply = d->m_manager->activateConnection("/org/freedesktop/NetworkManager/Settings/" + QByteArray::number(connId),
                                                  "/org/freedesktop/NetworkManager/Devices/" + QByteArray::number(deviceId),
                                                  specObj);
    reply.waitForFinished();
    if (!reply.isValid())
        return DUnexpected{emplace_tag::USE_EMPLACE, reply.error().type(), reply.error().message()};
    return getIdFromObjectPath(reply.value());
}

DExpected<NewConn>
DNetworkManager::addAndActivateConnection(const SettingDesc &conn, const quint64 &deviceId, const QByteArray specObj) const
{
    Q_D(const DNetworkManager);
    auto reply = d->m_manager->addAndActivateConnection(
        conn, "/org/freedesktop/NetworkManager/Devices/" + QByteArray::number(deviceId), specObj);
    reply.waitForFinished();
    if (!reply.isValid())
        return DUnexpected{emplace_tag::USE_EMPLACE, reply.error().type(), reply.error().message()};
    return NewConn{getIdFromObjectPath(reply.argumentAt<0>()), getIdFromObjectPath(reply.argumentAt<1>())};
}

DExpected<void> DNetworkManager::deactivateConnection(const quint64 &activeConnId) const
{
    Q_D(const DNetworkManager);
    auto reply = d->m_manager->deactivateConnection("/org/freedesktop/ActiveConnection/" + QByteArray::number(activeConnId));
    reply.waitForFinished();
    if (!reply.isValid())
        return DUnexpected{emplace_tag::USE_EMPLACE, reply.error().type(), reply.error().message()};
    return {};
}

DExpected<void> DNetworkManager::enable(const bool enabled) const
{
    Q_D(const DNetworkManager);
    auto reply = d->m_manager->enable(enabled);
    reply.waitForFinished();
    if (!reply.isValid())
        return DUnexpected{emplace_tag::USE_EMPLACE, reply.error().type(), reply.error().message()};
    return {};
}

DExpected<QMap<QString, QString>> DNetworkManager::permissions() const
{
    Q_D(const DNetworkManager);
    auto reply = d->m_manager->getPermissions();
    reply.waitForFinished();
    if (!reply.isValid())
        return DUnexpected{emplace_tag::USE_EMPLACE, reply.error().type(), reply.error().message()};
    return reply.value();
}

DExpected<NMConnectivityState> DNetworkManager::checkConnectivity() const
{
    Q_D(const DNetworkManager);
    auto reply = d->m_manager->checkConnectivity();
    reply.waitForFinished();
    if (!reply.isValid())
        return DUnexpected{emplace_tag::USE_EMPLACE, reply.error().type(), reply.error().message()};
    return static_cast<NMConnectivityState>(reply.value());
}

DNETWORKMANAGER_END_NAMESPACE
