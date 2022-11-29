// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DIPV6CONFIGINTERFACE_H
#define DIPV6CONFIGINTERFACE_H

#include "dnetworkmanager_global.h"
#include "dnetworkmanagertypes.h"
#include <QObject>
#include <QString>
#include <DDBusInterface>
#include <QDBusPendingReply>

DNETWORKMANAGER_BEGIN_NAMESPACE

using DTK_CORE_NAMESPACE::DDBusInterface;

class DIPv6ConfigInterface : public QObject
{
    Q_OBJECT
public:
    explicit DIPv6ConfigInterface(const QByteArray &path, QObject *parent = nullptr);
    ~DIPv6ConfigInterface() = default;

    Q_PROPERTY(QList<Config> addressData READ addressData NOTIFY addressDataChanged)
    Q_PROPERTY(QList<QByteArray> nameservers READ nameservers NOTIFY nameserversChanged)
    Q_PROPERTY(QString gateway READ gateway NOTIFY gatewayChanged)

    QList<Config> addressData() const;
    QList<QByteArray> nameservers() const;
    QString gateway() const;

signals:
    void addressDataChanged(const QList<Config> &addressData);
    void nameserversChanged(const QList<QByteArray> &nameservers);
    void gatewayChanged(const QString &gateway);

private:
    DDBusInterface *m_inter{nullptr};
};

DNETWORKMANAGER_END_NAMESPACE

#endif
