// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DGENERICDEVICE_H
#define DGENERICDEVICE_H

#include "ddevice.h"

DNETWORKMANAGER_BEGIN_NAMESPACE

class DGenericDevicePrivate;

class DGenericDevice : public DDevice
{
    Q_OBJECT
    Q_PROPERTY(QByteArray HwAddress READ HwAddress NOTIFY HwAddressChanged)
    Q_PROPERTY(QString typeDescription READ typeDescription NOTIFY typeDescriptionChanged)
public:
    explicit DGenericDevice(const quint64 id, QObject *parent = nullptr);
    ~DGenericDevice() = default;

    QByteArray HwAddress() const;
    QString typeDescription() const;

signals:
    void HwAddressChanged(const QByteArray &addr);
    void typeDescriptionChanged(const QString &desc);

private:
    Q_DECLARE_PRIVATE(DGenericDevice)
};

DNETWORKMANAGER_END_NAMESPACE

#endif
