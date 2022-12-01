// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DACTIVEVPNCONNECTIONINTERFACE_H
#define DACTIVEVPNCONNECTIONINTERFACE_H

#include "dactiveconnectioninterface.h"

DNETWORKMANAGER_BEGIN_NAMESPACE

using DTK_CORE_NAMESPACE::DDBusInterface;

class DActiveVpnConnectionInterface : public DActiveConnectionInterface
{
    Q_OBJECT
public:
    explicit DActiveVpnConnectionInterface(const QByteArray &path, QObject *parent = nullptr);
    ~DActiveVpnConnectionInterface() override = default;

    Q_PROPERTY(quint32 vpnState READ vpnState NOTIFY VpnStateChanged)
    Q_PROPERTY(QString banner READ banner NOTIFY bannerChanged)

    quint32 vpnState() const;
    QString banner() const;

signals:
    void VpnStateChanged(const quint32 state, const quint32 reason);
    void bannerChanged(const QString &banner);

private:
    DDBusInterface *m_vpninter{nullptr};
};

DNETWORKMANAGER_END_NAMESPACE

#endif
