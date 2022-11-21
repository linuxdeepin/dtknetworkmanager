// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dwireddevice_p.h"

DNETWORKMANAGER_BEGIN_NAMESPACE

DWiredDevicePrivate::DWiredDevicePrivate(const quint64 id, DWiredDevice *parent)
    : DDevicePrivate(id, parent)
    , m_wired(new DWiredDeviceInterface("/org/freedesktop/NetworkManager/Devices/" + QByteArray::number(id), this))
{
}

DWiredDevice::DWiredDevice(const quint64 id, QObject *parent)
    : DDevice(id, parent)
{
    Q_D(const DWiredDevice);

    connect(d->m_wired, &DWiredDeviceInterface::carrierChanged, this, &DWiredDevice::carrierChanged);

    connect(d->m_wired, &DWiredDeviceInterface::HwAddressChanged, this, [this](const QString &addr) {
        emit this->HwAddressChanged(addr.toUtf8());
    });

    connect(d->m_wired, &DWiredDeviceInterface::permHwAddressChanged, this, [this](const QString &address) {
        emit this->permHwAddressChanged(address.toUtf8());
    });

    connect(d->m_wired, &DWiredDeviceInterface::speedChanged, this, &DWiredDevice::speedChanged);

    connect(d->m_wired, &DWiredDeviceInterface::S390SubchannelsChanged, this, &DWiredDevice::S390SubchannelsChanged);
}

QByteArray DWiredDevice::HwAddress() const
{
    Q_D(const DWiredDevice);
    return d->m_wired->HwAddress().toUtf8();
}

QByteArray DWiredDevice::permHwAddress() const
{
    Q_D(const DWiredDevice);
    return d->m_wired->permHwAddress().toUtf8();
}

quint32 DWiredDevice::speed() const
{
    Q_D(const DWiredDevice);
    return d->m_wired->speed();
}

QList<QString> DWiredDevice::S390Subchannels() const
{
    Q_D(const DWiredDevice);
    return d->m_wired->S390Subchannels();
}

bool DWiredDevice::carrier() const
{
    Q_D(const DWiredDevice);
    return d->m_wired->carrier();
}

DNETWORKMANAGER_END_NAMESPACE
