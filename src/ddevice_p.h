// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DDEVICEPRIVATE_P_H
#define DDEVICEPRIVATE_P_H

#include "dbus/ddeviceInterface.h"

DNETWORKMANAGER_BEGIN_NAMESPACE

class DDevice;

class DDevicePrivate : public QObject
{
    Q_OBJECT
public:
    explicit DDevicePrivate(const quint64 deviceId, DDevice *parent = nullptr);
    ~DDevicePrivate() = default;

    DDevice *q_ptr{nullptr};
    DDeviceInterface *m_device{nullptr};
    Q_DECLARE_PUBLIC(DDevice)
};

DNETWORKMANAGER_END_NAMESPACE

#endif
