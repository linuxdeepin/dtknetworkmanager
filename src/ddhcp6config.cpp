// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "ddhcp6config.h"
#include "ddhcp6config_p.h"

DNETWORKMANAGER_BEGIN_NAMESPACE

DDHCP6ConfigPrivate::DDHCP6ConfigPrivate(const quint64 id, DDHCP6Config *parent)
    : q_ptr(parent)
    , m_dhcp6(new DDHCP6ConfigInterface("/org/freedesktop/NetworkManager/DHCP6Config/" + QByteArray::number(id), this))
{
}

DDHCP6Config::DDHCP6Config(const quint64 id, QObject *parent)
    : QObject(parent)
    , d_ptr(new DDHCP6ConfigPrivate(id, this))
{
    Q_D(const DDHCP6Config);
    connect(d->m_dhcp6, &DDHCP6ConfigInterface::optionsChanged, this, &DDHCP6Config::optionsChanged);
}

Config DDHCP6Config::options() const
{
    Q_D(const DDHCP6Config);
    return d->m_dhcp6->options();
}

DNETWORKMANAGER_END_NAMESPACE
