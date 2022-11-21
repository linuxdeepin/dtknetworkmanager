// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dtundevice_p.h"

DNETWORKMANAGER_BEGIN_NAMESPACE

DTunDevicePrivate::DTunDevicePrivate(const quint64 id, DTunDevice *parent)
    : DDevicePrivate(id, parent)
    , m_tun(new DTunDeviceInterface("/org/freedesktop/NetworkManager/Devices/" + QByteArray::number(id), this))
{
}

DTunDevice::DTunDevice(const quint64 id, QObject *parent)
    : DDevice(id, parent)
{
    Q_D(const DTunDevice);
    connect(d->m_tun, &DTunDeviceInterface::HwAddressChanged, this, [this](const QString &addr) {
        emit this->HwAddressChanged(addr.toUtf8());
    });
}

QByteArray DTunDevice::HwAddress() const
{
    Q_D(const DTunDevice);
    return d->m_tun->HwAddress().toUtf8();
}

DNETWORKMANAGER_END_NAMESPACE
