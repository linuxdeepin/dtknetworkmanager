// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DADSLDEVICEINTERFACE_H
#define DADSLDEVICEINTERFACE_H

#include "ddeviceInterface.h"

DNETWORKMANAGER_BEGIN_NAMESPACE

using DTK_CORE_NAMESPACE::DDBusInterface;

class DAdslDeviceInterface : public DDeviceInterface
{
    Q_OBJECT
public:
    explicit DAdslDeviceInterface(const QByteArray &path, QObject *parent = nullptr);
    ~DAdslDeviceInterface() override = default;

    Q_PROPERTY(bool carrier READ carrier NOTIFY CarrierChanged)
    bool carrier() const;

signals:
    void CarrierChanged(const bool found);

private:
    DDBusInterface *m_adslInter{nullptr};
};

DNETWORKMANAGER_END_NAMESPACE
#endif
