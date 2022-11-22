// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dipv6config.h"
#include "dipv6config_p.h"

DNETWORKMANAGER_BEGIN_NAMESPACE

DIPv6ConfigPrivate::DIPv6ConfigPrivate(const quint64 id, DIPv6Config *parent)
    : q_ptr(parent)
    , m_ipv6(new DIPv6ConfigInterface("/org/freedesktop/NetworkManager/IP6Config/" + QByteArray::number(id), this))
{
}

DIPv6Config::DIPv6Config(const quint64 id, QObject *parent)
    : QObject(parent)
    , d_ptr(new DIPv6ConfigPrivate(id, this))
{
    Q_D(const DIPv6Config);
    connect(d->m_ipv6, &DIPv6ConfigInterface::addressDataChanged, this, &DIPv6Config::addressDataChanged);

    connect(d->m_ipv6, &DIPv6ConfigInterface::nameserversChanged, this, [this](const QList<QString> &nameservers) {
        QList<QByteArray> ret;
        for (const auto &it : nameservers)
            ret.append(it.toUtf8());
        emit this->nameserversChanged(ret);
    });

    connect(d->m_ipv6, &DIPv6ConfigInterface::gatewayChanged, this, [this](const QString &gateway) {
        emit this->gatewayChanged(gateway.toUtf8());
    });
}

QList<Config> DIPv6Config::addressData() const
{
    Q_D(const DIPv6Config);
    return d->m_ipv6->addressData();
}

QList<QByteArray> DIPv6Config::nameservers() const
{
    Q_D(const DIPv6Config);
    QList<QByteArray> ret;
    for (const auto &it : d->m_ipv6->nameservers())
        ret.append(it.toUtf8());
    return ret;
}

QByteArray DIPv6Config::gateway() const
{
    Q_D(const DIPv6Config);
    return d->m_ipv6->gateway().toUtf8();
}

DNETWORKMANAGER_END_NAMESPACE
