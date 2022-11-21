// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dadsldevice_p.h"

DNETWORKMANAGER_BEGIN_NAMESPACE

DAdslDevicePrivate::DAdslDevicePrivate(const quint64 id, DAdslDevice *parent)
    : DDevicePrivate(id, parent)
    , m_adsl(new DAdslDeviceInterface("/org/freedesktop/NetworkManager/Devices/" + QByteArray::number(id), this))
{
}

DAdslDevice::DAdslDevice(const quint64 id, QObject *parent)
    : DDevice(id, parent)
{
    Q_D(const DAdslDevice);
    connect(d->m_adsl, &DAdslDeviceInterface::carrierChanged, this, &DAdslDevice::carrierChanged);
}

bool DAdslDevice::carrier() const
{
    Q_D(const DAdslDevice);
    return d->m_adsl->carrier();
}

DNETWORKMANAGER_END_NAMESPACE
