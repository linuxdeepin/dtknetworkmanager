// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DACTIVECONNECTIONINTERFACE_H
#define DACTIVECONNECTIONINTERFACE_H

#include "dnetworkmanager_global.h"
#include "dnetworkmanagertypes.h"
#include <DDBusInterface>
#include <QList>
#include <QDBusObjectPath>

DNETWORKMANAGER_BEGIN_NAMESPACE

using DTK_CORE_NAMESPACE::DDBusInterface;

class DActiveConnectionInterface : public QObject
{
    Q_OBJECT
public:
    explicit DActiveConnectionInterface(const QByteArray &Path, QObject *parent = nullptr);
    ~DActiveConnectionInterface() = default;

    Q_PROPERTY(QList<QDBusObjectPath> devices READ devices NOTIFY devicesChanged)
    Q_PROPERTY(bool vpn READ vpn NOTIFY vpnChanged)
    Q_PROPERTY(QDBusObjectPath connection READ connection NOTIFY connectionChanged)
    Q_PROPERTY(QDBusObjectPath DHCP4Config READ DHCP4Config NOTIFY DHCP4ConfigChanged)
    Q_PROPERTY(QDBusObjectPath DHCP6Config READ DHCP6Config NOTIFY DHCP6ConfigChanged)
    Q_PROPERTY(QDBusObjectPath IP4Config READ IP4Config NOTIFY IP4ConfigChanged)
    Q_PROPERTY(QDBusObjectPath IP6Config READ IP6Config NOTIFY IP6ConfigChanged)
    Q_PROPERTY(QDBusObjectPath specificObject READ specificObject NOTIFY specificObjectChanged)
    Q_PROPERTY(QString id READ id NOTIFY idChanged)
    Q_PROPERTY(QString uuid READ uuid NOTIFY uuidChanged)
    Q_PROPERTY(quint32 state READ state NOTIFY StateChanged)

    QList<QDBusObjectPath> devices() const;
    bool vpn() const;
    QDBusObjectPath connection() const;
    QDBusObjectPath DHCP4Config() const;
    QDBusObjectPath DHCP6Config() const;
    QDBusObjectPath IP4Config() const;
    QDBusObjectPath IP6Config() const;
    QDBusObjectPath specificObject() const;
    QString id() const;
    QString uuid() const;
    quint32 state() const;

signals:
    void devicesChanged(const QList<QDBusObjectPath> &devices);
    void vpnChanged(const bool vpn);
    void connectionChanged(const QDBusObjectPath &connection);
    void DHCP4ConfigChanged(const QDBusObjectPath &config);
    void DHCP6ConfigChanged(const QDBusObjectPath &config);
    void IP4ConfigChanged(const QDBusObjectPath &config);
    void IP6ConfigChanged(const QDBusObjectPath &config);
    void specificObjectChanged(const QDBusObjectPath &specObj);
    void idChanged(const QString &id);
    void uuidChanged(const QString &uuid);
    void StateChanged(const quint32 state, const quint32 reason);

private:
    DDBusInterface *m_inter{nullptr};
};

DNETWORKMANAGER_END_NAMESPACE

#endif
