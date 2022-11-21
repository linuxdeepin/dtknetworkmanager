// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dgenericdevice_p.h"

DNETWORKMANAGER_BEGIN_NAMESPACE

DGenericDevicePrivate::DGenericDevicePrivate(const quint64 id, DGenericDevice *parent)
    : DDevicePrivate(id, parent)
    , m_generic(new DGenericDeviceInterface("/org/freedesktop/NetworkManager/Devices/" + QByteArray::number(id), this))
{
}

DGenericDevice::DGenericDevice(const quint64 id, QObject *parent)
    : DDevice(id, parent)
{
    Q_D(const DGenericDevice);
    connect(d->m_generic, &DGenericDeviceInterface::HwAddressChanged, this, [this](const QString &addr) {
        emit this->HwAddressChanged(addr.toUtf8());
    });
    connect(d->m_generic, &DGenericDeviceInterface::typeDescriptionChanged, this, &DGenericDevice::typeDescriptionChanged);
}

QByteArray DGenericDevice::HwAddress() const
{
    Q_D(const DGenericDevice);
    return d->m_generic->HwAddress().toUtf8();
}

QString DGenericDevice::typeDescription() const
{
    Q_D(const DGenericDevice);
    return d->m_generic->typeDescription();
}

DNETWORKMANAGER_END_NAMESPACE
