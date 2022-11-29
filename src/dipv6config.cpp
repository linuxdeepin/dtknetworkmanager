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

    connect(d->m_ipv6, &DIPv6ConfigInterface::nameserversChanged, this, [this](const QList<QByteArray> &nameservers) {
        QList<QHostAddress> ret;
        for (const QByteArray &nameserver : nameservers) {
            Q_IPV6ADDR address;
            for (int i = 0; i < 16; i++) {
                address[i] = static_cast<quint8>(nameserver[i]);
            }
            ret.append(QHostAddress(address));
        }
        emit this->nameserversChanged(ret);
    });

    connect(d->m_ipv6, &DIPv6ConfigInterface::gatewayChanged, this, [this](const QString &gateway) {
        emit this->gatewayChanged(QHostAddress(gateway));
    });
}

QList<Config> DIPv6Config::addressData() const
{
    Q_D(const DIPv6Config);
    return d->m_ipv6->addressData();
}

QList<QHostAddress> DIPv6Config::nameservers() const
{
    Q_D(const DIPv6Config);
    QList<QHostAddress> ret;
    for (const QByteArray &nameserver : d->m_ipv6->nameservers()) {
        Q_IPV6ADDR address;
        for (int i = 0; i < 16; i++) {
            address[i] = static_cast<quint8>(nameserver[i]);
        }
        ret.append(QHostAddress(address));
    }
    return ret;
}

QHostAddress DIPv6Config::gateway() const
{
    Q_D(const DIPv6Config);
    return QHostAddress(d->m_ipv6->gateway());
}

DNETWORKMANAGER_END_NAMESPACE
