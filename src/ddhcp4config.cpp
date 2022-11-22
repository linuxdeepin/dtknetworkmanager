// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "ddhcp4config.h"
#include "ddhcp4config_p.h"

DNETWORKMANAGER_BEGIN_NAMESPACE

DDHCP4ConfigPrivate::DDHCP4ConfigPrivate(const quint64 id, DDHCP4Config *parent)
    : q_ptr(parent)
    , m_dhcp4(new DDHCP4ConfigInterface("/org/freedesktop/NetworkManager/DHCP4Config/" + QByteArray::number(id), this))
{
}

DDHCP4Config::DDHCP4Config(const quint64 id, QObject *parent)
    : QObject(parent)
    , d_ptr(new DDHCP4ConfigPrivate(id, this))
{
    Q_D(const DDHCP4Config);
    connect(d->m_dhcp4, &DDHCP4ConfigInterface::optionsChanged, this, &DDHCP4Config::optionsChanged);
}

Config DDHCP4Config::options() const
{
    Q_D(const DDHCP4Config);
    return d->m_dhcp4->options();
}

DNETWORKMANAGER_END_NAMESPACE
