// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "ddevice_p.h"
#include "dnmutils.h"

DNETWORKMANAGER_BEGIN_NAMESPACE

using DCORE_NAMESPACE::DUnexpected;
using DCORE_NAMESPACE::emplace_tag;

DDevicePrivate::DDevicePrivate(const quint64 deviceId, DDevice *parent)
#ifdef USE_FAKE_INTERFACE
    : m_device(new DDeviceInterface("/com/deepin/FakeNetworkManager/Devices/" + QByteArray::number(deviceId), this))
#else
    : m_device(new DDeviceInterface("/org/freedesktop/NetworkManager/Devices/" + QByteArray::number(deviceId), this))
#endif
    , q_ptr(parent)
{
}

DDevicePrivate::~DDevicePrivate() = default;

DDevice::DDevice(const quint64 deviceId, QObject *parent)
    : QObject(parent)
    , d_ptr(new DDevicePrivate(deviceId, this))
{
    Q_D(const DDevice);
    connect(d->m_device, &DDeviceInterface::availableConnectionsChanged, this, [this](const QList<QDBusObjectPath> &conns) {
        QList<quint64> ret;
        for (const auto &it : conns)
            ret.append(getIdFromObjectPath(it));
        emit this->availableConnectionsChanged(ret);
    });

    connect(d->m_device,
            &DDeviceInterface::stateChanged,
            this,
            [this](const quint32 newSatate, const quint32 oldState, const quint32 reason) {
                emit this->deviceStateChanged(static_cast<NMDeviceState>(newSatate),
                                              static_cast<NMDeviceState>(oldState),
                                              static_cast<NMDeviceStateReason>(reason));
            });

    connect(d->m_device, &DDeviceInterface::autoconnectChanged, this, &DDevice::autoconnectChanged);

    connect(d->m_device, &DDeviceInterface::managedChanged, this, &DDevice::managedChanged);

    connect(d->m_device, &DDeviceInterface::activeConnectionChanged, this, [this](const QDBusObjectPath &conn) {
        emit this->activeConnectionChanged(getIdFromObjectPath(conn));
    });

    connect(d->m_device, &DDeviceInterface::DHCP4ConfigChanged, this, [this](const QDBusObjectPath &config) {
        emit this->DHCP4ConfigChanged(getIdFromObjectPath(config));
    });

    connect(d->m_device, &DDeviceInterface::DHCP6ConfigChanged, this, [this](const QDBusObjectPath &config) {
        emit this->DHCP6ConfigChanged(getIdFromObjectPath(config));
    });

    connect(d->m_device, &DDeviceInterface::IPv4ConfigChanged, this, [this](const QDBusObjectPath &config) {
        emit this->IPv4ConfigChanged(getIdFromObjectPath(config));
    });

    connect(d->m_device, &DDeviceInterface::IPv6ConfigChanged, this, [this](const QDBusObjectPath &config) {
        emit this->IPv6ConfigChanged(getIdFromObjectPath(config));
    });

    connect(d->m_device, &DDeviceInterface::driverChanged, this, [this](const QString &driver) {
        emit this->driverChanged(driver.toUtf8());
    });

    connect(d->m_device, &DDeviceInterface::interfaceChanged, this, [this](const QString &ifc) {
        emit this->interfaceChanged(ifc.toUtf8());
    });

    connect(
        d->m_device, &DDeviceInterface::udiChanged, this, [this](const QString &udi) { emit this->udiChanged(udi.toUtf8()); });

    connect(d->m_device, &DDeviceInterface::deviceTypeChanged, this, [this](const quint32 type) {
        emit this->deviceTypeChanged(static_cast<NMDeviceType>(type));
    });

    connect(d->m_device, &DDeviceInterface::interfaceFlagsChanged, this, [this](const quint32 flags) {
        emit this->interfaceFlagsChanged(DeviceInterfaceFlags{flags});
    });

    connect(d->m_device, &DDeviceInterface::refreshRateMsChanged, this, &DDevice::refreshRateMsChanged);

    connect(d->m_device, &DDeviceInterface::rxBytesChanged, this, &DDevice::rxBytesChanged);

    connect(d->m_device, &DDeviceInterface::txBytesChanged, this, &DDevice::txBytesChanged);
}

DDevice::DDevice(DDevicePrivate &other, QObject *parent)
    : QObject(parent)
    , d_ptr(&other)
{
    Q_D(const DDevice);
    connect(d->m_device, &DDeviceInterface::availableConnectionsChanged, this, [this](const QList<QDBusObjectPath> &conns) {
        QList<quint64> ret;
        for (const auto &it : conns)
            ret.append(getIdFromObjectPath(it));
        emit this->availableConnectionsChanged(ret);
    });

    connect(d->m_device,
            &DDeviceInterface::stateChanged,
            this,
            [this](const quint32 newSatate, const quint32 oldState, const quint32 reason) {
                emit this->deviceStateChanged(static_cast<NMDeviceState>(newSatate),
                                              static_cast<NMDeviceState>(oldState),
                                              static_cast<NMDeviceStateReason>(reason));
            });

    connect(d->m_device, &DDeviceInterface::autoconnectChanged, this, &DDevice::autoconnectChanged);

    connect(d->m_device, &DDeviceInterface::managedChanged, this, &DDevice::managedChanged);

    connect(d->m_device, &DDeviceInterface::activeConnectionChanged, this, [this](const QDBusObjectPath &conn) {
        emit this->activeConnectionChanged(getIdFromObjectPath(conn));
    });

    connect(d->m_device, &DDeviceInterface::DHCP4ConfigChanged, this, [this](const QDBusObjectPath &config) {
        emit this->DHCP4ConfigChanged(getIdFromObjectPath(config));
    });

    connect(d->m_device, &DDeviceInterface::DHCP6ConfigChanged, this, [this](const QDBusObjectPath &config) {
        emit this->DHCP6ConfigChanged(getIdFromObjectPath(config));
    });

    connect(d->m_device, &DDeviceInterface::IPv4ConfigChanged, this, [this](const QDBusObjectPath &config) {
        emit this->IPv4ConfigChanged(getIdFromObjectPath(config));
    });

    connect(d->m_device, &DDeviceInterface::IPv6ConfigChanged, this, [this](const QDBusObjectPath &config) {
        emit this->IPv6ConfigChanged(getIdFromObjectPath(config));
    });

    connect(d->m_device, &DDeviceInterface::driverChanged, this, [this](const QString &driver) {
        emit this->driverChanged(driver.toUtf8());
    });

    connect(d->m_device, &DDeviceInterface::interfaceChanged, this, [this](const QString &ifc) {
        emit this->interfaceChanged(ifc.toUtf8());
    });

    connect(
        d->m_device, &DDeviceInterface::udiChanged, this, [this](const QString &udi) { emit this->udiChanged(udi.toUtf8()); });

    connect(d->m_device, &DDeviceInterface::deviceTypeChanged, this, [this](const quint32 type) {
        emit this->deviceTypeChanged(static_cast<NMDeviceType>(type));
    });

    connect(d->m_device, &DDeviceInterface::interfaceFlagsChanged, this, [this](const quint32 flags) {
        emit this->interfaceFlagsChanged(static_cast<NMDeviceInterfaceFlags>(flags));
    });

    connect(d->m_device, &DDeviceInterface::refreshRateMsChanged, this, &DDevice::refreshRateMsChanged);

    connect(d->m_device, &DDeviceInterface::rxBytesChanged, this, &DDevice::rxBytesChanged);

    connect(d->m_device, &DDeviceInterface::txBytesChanged, this, &DDevice::txBytesChanged);
}

DDevice::~DDevice() = default;

QList<quint64> DDevice::availableConnections() const
{
    Q_D(const DDevice);
    QList<quint64> ret;
    for (const auto &it : d->m_device->availableConnections())
        ret.append(getIdFromObjectPath(it));
    return ret;
}

bool DDevice::autoconnect() const
{
    Q_D(const DDevice);
    return d->m_device->autoconnect();
}

void DDevice::setAutoconnect(const bool autoconnect) const
{
    Q_D(const DDevice);
    d->m_device->setAutoconnect(autoconnect);
}

bool DDevice::managed() const
{
    Q_D(const DDevice);
    return d->m_device->managed();
}

void DDevice::setManaged(const bool managed) const
{
    Q_D(const DDevice);
    d->m_device->setManaged(managed);
}

quint64 DDevice::activeConnection() const
{
    Q_D(const DDevice);
    return getIdFromObjectPath(d->m_device->activeConnection());
}

quint64 DDevice::DHCP4Config() const
{
    Q_D(const DDevice);
    return getIdFromObjectPath(d->m_device->DHCP4Config());
}

quint64 DDevice::DHCP6Config() const
{
    Q_D(const DDevice);
    return getIdFromObjectPath(d->m_device->DHCP6Config());
}

quint64 DDevice::IPv4Config() const
{
    Q_D(const DDevice);
    return getIdFromObjectPath(d->m_device->IPv4Config());
}

quint64 DDevice::IPv6Config() const
{
    Q_D(const DDevice);
    return getIdFromObjectPath(d->m_device->IPv6Config());
}

QByteArray DDevice::driver() const
{
    Q_D(const DDevice);
    return d->m_device->driver().toUtf8();
}

QByteArray DDevice::interface() const
{
    Q_D(const DDevice);
    return d->m_device->interface().toUtf8();
}

QByteArray DDevice::udi() const
{
    Q_D(const DDevice);
    return d->m_device->udi().toUtf8();
}

NMDeviceType DDevice::deviceType() const
{
    Q_D(const DDevice);
    return static_cast<NMDeviceType>(d->m_device->deviceType());
}

DDevice::DeviceInterfaceFlags DDevice::interfaceFlags() const
{
    Q_D(const DDevice);
    return DDevice::DeviceInterfaceFlags{d->m_device->interfaceFlags()};
}

NMDeviceState DDevice::deviceState() const
{
    Q_D(const DDevice);
    return static_cast<NMDeviceState>(d->m_device->state());
}

quint32 DDevice::refreshRateMs() const
{
    Q_D(const DDevice);
    return d->m_device->refreshRateMs();
}

void DDevice::setRefreshRateMs(const quint32 newRate) const
{
    Q_D(const DDevice);
    d->m_device->setRefreshRateMs(newRate);
}

quint32 DDevice::rxBytes() const
{
    Q_D(const DDevice);
    return d->m_device->rxBytes();
}

quint32 DDevice::txBytes() const
{
    Q_D(const DDevice);
    return d->m_device->txBytes();
}

DExpected<void> DDevice::disconnect() const
{
    Q_D(const DDevice);
    auto reply = d->m_device->disconnect();
    reply.waitForFinished();
    if (!reply.isValid())
        return DUnexpected{emplace_tag::USE_EMPLACE, reply.error().type(), reply.error().message()};
    return {};
}

DNETWORKMANAGER_END_NAMESPACE
