// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DACTIVECONNECTION_H
#define DACTIVECONNECTION_H

#include "dnetworkmanagertypes.h"

DNETWORKMANAGER_BEGIN_NAMESPACE

class DActiveConnectionPrivate;

class DActiveConnection : public QObject
{
    Q_OBJECT
public:
    explicit DActiveConnection(const quint64 activeConnId, QObject *parent = nullptr);
    ~DActiveConnection() = default;

    Q_PROPERTY(QList<quint64> devices READ devices NOTIFY devicesChanged)
    Q_PROPERTY(bool vpn READ vpn NOTIFY vpnChanged)
    Q_PROPERTY(quint64 connection READ connection NOTIFY connectionChanged)
    Q_PROPERTY(quint64 DHCP4Config READ DHCP4Config NOTIFY DHCP4ConfigChanged)
    Q_PROPERTY(quint64 DHCP6Config READ DHCP6Config NOTIFY DHCP6ConfigChanged)
    Q_PROPERTY(quint64 IP4Config READ IP4Config NOTIFY IP4ConfigChanged)
    Q_PROPERTY(quint64 IP6Config READ IP6Config NOTIFY IP6ConfigChanged)
    Q_PROPERTY(QByteArray specificObject READ specificObject NOTIFY specificObjectChanged)
    Q_PROPERTY(QString connecionId READ connecionId NOTIFY connecionIdChanged)
    Q_PROPERTY(QString connectionType READ connectionType NOTIFY connectionTypeChanged)
    Q_PROPERTY(QByteArray UUID READ UUID NOTIFY UUIDChanged)
    Q_PROPERTY(NMActiveConnectionState connectionState READ connectionState NOTIFY connectionStateChanged)

    QList<quint64> devices() const;
    bool vpn() const;
    quint64 connection() const;
    quint64 DHCP4Config() const;
    quint64 DHCP6Config() const;
    quint64 IP4Config() const;
    quint64 IP6Config() const;
    QByteArray specificObject() const;
    QString connecionId() const;
    QByteArray connectionType() const;
    QByteArray UUID() const;
    NMActiveConnectionState connectionState() const;

signals:
    void devicesChanged(const QList<quint64> &devices);
    void vpnChanged(const bool vpn);
    void connectionChanged(const quint64 &connection);
    void DHCP4ConfigChanged(const quint64 &config);
    void DHCP6ConfigChanged(const quint64 &config);
    void IP4ConfigChanged(const quint64 &config);
    void IP6ConfigChanged(const quint64 &config);
    void specificObjectChanged(const QByteArray &specObj);
    void connecionIdChanged(const QString &id);
    void connectionTypeChanged(const QByteArray &type);
    void UUIDChanged(const QByteArray &UUID);
    void connectionStateChanged(const NMActiveConnectionState state, const NMActiveConnectionStateReason reason);

private:
    QScopedPointer<DActiveConnectionPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DActiveConnection)
};

DNETWORKMANAGER_END_NAMESPACE

#endif
