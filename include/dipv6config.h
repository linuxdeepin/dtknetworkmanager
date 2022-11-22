// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DIPV6CONFIG_H
#define DIPV6CONFIG_H

#include "dnetworkmanagertypes.h"

DNETWORKMANAGER_BEGIN_NAMESPACE

class DIPv6ConfigPrivate;

class DIPv6Config : public QObject
{
    Q_OBJECT
public:
    explicit DIPv6Config(const quint64 id, QObject *parent = nullptr);
    ~DIPv6Config() = default;

    Q_PROPERTY(QList<Config> addressData READ addressData NOTIFY addressDataChanged)
    Q_PROPERTY(QList<QByteArray> nameservers READ nameservers NOTIFY nameserversChanged)
    Q_PROPERTY(QByteArray gateway READ gateway NOTIFY gatewayChanged)

    QList<Config> addressData() const;
    QList<QByteArray> nameservers() const;
    QByteArray gateway() const;

signals:
    void addressDataChanged(const QList<Config> &addrs) const;
    void nameserversChanged(const QList<QByteArray> &nameserver) const;
    void gatewayChanged(const QByteArray &gateway);

private:
    QScopedPointer<DIPv6ConfigPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DIPv6Config)
};

DNETWORKMANAGER_END_NAMESPACE
#endif
