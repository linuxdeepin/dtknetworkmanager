// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dactiveconnection_p.h"
#include "dnmutils.h"

DNETWORKMANAGER_BEGIN_NAMESPACE

DActiveConnectionPrivate::DActiveConnectionPrivate(const quint64 activeConnId, DActiveConnection *parent)
    : q_ptr(parent)
#ifdef USE_FAKE_INTERFACE
    , m_activeConn(new DActiveConnectionInterface(
          "/com/deepin/FakeNetworkManager/ActiveConnection/" + QByteArray::number(activeConnId), this))
#else
    , m_activeConn(new DActiveConnectionInterface(
          "/org/freedesktop/NetworkManager/ActiveConnection/" + QByteArray::number(activeConnId), this))
#endif
{
}

DActiveConnectionPrivate::~DActiveConnectionPrivate() = default;

DActiveConnection::DActiveConnection(const quint64 activeConnId, QObject *parent)
    : QObject(parent)
    , d_ptr(new DActiveConnectionPrivate(activeConnId, this))
{
    Q_D(const DActiveConnection);
    connect(d->m_activeConn, &DActiveConnectionInterface::devicesChanged, this, [this](const QList<QDBusObjectPath> &devices) {
        QList<quint64> ret;
        for (const auto &it : devices)
            ret.append(getIdFromObjectPath(it));
        emit this->devicesChanged(ret);
    });
    connect(d->m_activeConn, &DActiveConnectionInterface::vpnChanged, this, &DActiveConnection::vpnChanged);
    connect(d->m_activeConn, &DActiveConnectionInterface::connectionChanged, this, [this](const QDBusObjectPath &connection) {
        emit this->connectionChanged(getIdFromObjectPath(connection));
    });
    connect(d->m_activeConn, &DActiveConnectionInterface::DHCP4ConfigChanged, this, [this](const QDBusObjectPath &config) {
        emit this->DHCP4ConfigChanged(getIdFromObjectPath(config));
    });
    connect(d->m_activeConn, &DActiveConnectionInterface::DHCP6ConfigChanged, this, [this](const QDBusObjectPath &config) {
        emit this->DHCP6ConfigChanged(getIdFromObjectPath(config));
    });
    connect(d->m_activeConn, &DActiveConnectionInterface::IP4ConfigChanged, this, [this](const QDBusObjectPath &config) {
        emit this->IP4ConfigChanged(getIdFromObjectPath(config));
    });
    connect(d->m_activeConn, &DActiveConnectionInterface::IP6ConfigChanged, this, [this](const QDBusObjectPath &config) {
        emit this->IP6ConfigChanged(getIdFromObjectPath(config));
    });
    connect(d->m_activeConn, &DActiveConnectionInterface::specificObjectChanged, this, [this](const QDBusObjectPath &specObj) {
        emit this->specificObjectChanged(specObj.path().toUtf8());
    });
    connect(d->m_activeConn, &DActiveConnectionInterface::idChanged, this, &DActiveConnection::connecionIdChanged);
    connect(d->m_activeConn, &DActiveConnectionInterface::uuidChanged, this, [this](const QString &uuid) {
        emit this->UUIDChanged(uuid.toUtf8());
    });
    connect(d->m_activeConn, &DActiveConnectionInterface::typeChanged, this, [this](const QString &type) {
        emit this->connectionTypeChanged(type.toUtf8());
    });
    connect(d->m_activeConn, &DActiveConnectionInterface::stateChanged, this, [this](const quint32 state, const quint32 reason) {
        emit this->connectionStateChanged(static_cast<NMActiveConnectionState>(state),
                                          static_cast<NMActiveConnectionStateReason>(reason));
    });
}

DActiveConnection::DActiveConnection(DActiveConnectionPrivate &other, QObject *parent)
    : QObject(parent)
    , d_ptr(&other)
{
    Q_D(DActiveConnection);
    connect(d->m_activeConn, &DActiveConnectionInterface::devicesChanged, this, [this](const QList<QDBusObjectPath> &devices) {
        QList<quint64> ret;
        for (const auto &it : devices)
            ret.append(getIdFromObjectPath(it));
        emit this->devicesChanged(ret);
    });
    connect(d->m_activeConn, &DActiveConnectionInterface::vpnChanged, this, &DActiveConnection::vpnChanged);
    connect(d->m_activeConn, &DActiveConnectionInterface::connectionChanged, this, [this](const QDBusObjectPath &connection) {
        emit this->connectionChanged(getIdFromObjectPath(connection));
    });
    connect(d->m_activeConn, &DActiveConnectionInterface::DHCP4ConfigChanged, this, [this](const QDBusObjectPath &config) {
        emit this->DHCP4ConfigChanged(getIdFromObjectPath(config));
    });
    connect(d->m_activeConn, &DActiveConnectionInterface::DHCP6ConfigChanged, this, [this](const QDBusObjectPath &config) {
        emit this->DHCP6ConfigChanged(getIdFromObjectPath(config));
    });
    connect(d->m_activeConn, &DActiveConnectionInterface::IP4ConfigChanged, this, [this](const QDBusObjectPath &config) {
        emit this->IP4ConfigChanged(getIdFromObjectPath(config));
    });
    connect(d->m_activeConn, &DActiveConnectionInterface::IP6ConfigChanged, this, [this](const QDBusObjectPath &config) {
        emit this->IP6ConfigChanged(getIdFromObjectPath(config));
    });
    connect(d->m_activeConn, &DActiveConnectionInterface::specificObjectChanged, this, [this](const QDBusObjectPath &specObj) {
        emit this->specificObjectChanged(specObj.path().toUtf8());
    });
    connect(d->m_activeConn, &DActiveConnectionInterface::idChanged, this, &DActiveConnection::connecionIdChanged);
    connect(d->m_activeConn, &DActiveConnectionInterface::uuidChanged, this, [this](const QString &uuid) {
        emit this->UUIDChanged(uuid.toUtf8());
    });
    connect(d->m_activeConn, &DActiveConnectionInterface::typeChanged, this, [this](const QString &type) {
        emit this->connectionTypeChanged(type.toUtf8());
    });
    connect(d->m_activeConn, &DActiveConnectionInterface::stateChanged, this, [this](const quint32 state, const quint32 reason) {
        emit this->connectionStateChanged(static_cast<NMActiveConnectionState>(state),
                                          static_cast<NMActiveConnectionStateReason>(reason));
    });
}

DActiveConnection::~DActiveConnection() = default;

QList<quint64> DActiveConnection::devices() const
{
    Q_D(const DActiveConnection);
    QList<quint64> ret;
    for (const auto &it : d->m_activeConn->devices())
        ret.append(getIdFromObjectPath(it));
    return ret;
}

bool DActiveConnection::vpn() const
{
    Q_D(const DActiveConnection);
    return d->m_activeConn->vpn();
}

quint64 DActiveConnection::connection() const
{
    Q_D(const DActiveConnection);
    return getIdFromObjectPath(d->m_activeConn->connection());
}

quint64 DActiveConnection::DHCP4Config() const
{
    Q_D(const DActiveConnection);
    return getIdFromObjectPath(d->m_activeConn->DHCP4Config());
}

quint64 DActiveConnection::DHCP6Config() const
{
    Q_D(const DActiveConnection);
    return getIdFromObjectPath(d->m_activeConn->DHCP6Config());
}

quint64 DActiveConnection::IP4Config() const
{
    Q_D(const DActiveConnection);
    return getIdFromObjectPath(d->m_activeConn->IP4Config());
}

quint64 DActiveConnection::IP6Config() const
{
    Q_D(const DActiveConnection);
    return getIdFromObjectPath(d->m_activeConn->IP6Config());
}

QByteArray DActiveConnection::specificObject() const
{
    Q_D(const DActiveConnection);
    return d->m_activeConn->specificObject().path().toUtf8();
}

QString DActiveConnection::connecionId() const
{
    Q_D(const DActiveConnection);
    return d->m_activeConn->id();
}

QByteArray DActiveConnection::connectionType() const
{
    Q_D(const DActiveConnection);
    return d->m_activeConn->type().toUtf8();
}

QByteArray DActiveConnection::UUID() const
{
    Q_D(const DActiveConnection);
    return d->m_activeConn->uuid().toUtf8();
}

NMActiveConnectionState DActiveConnection::connectionState() const
{
    Q_D(const DActiveConnection);
    return static_cast<NMActiveConnectionState>(d->m_activeConn->state());
}

DNETWORKMANAGER_END_NAMESPACE
