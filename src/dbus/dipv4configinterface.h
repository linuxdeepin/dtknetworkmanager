// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DIPV4CONFIGINTERFACE_H
#define DIPV4CONFIGINTERFACE_H

#include "dnetworkmanager_global.h"
#include "dnetworkmanagertypes.h"
#include <QObject>
#include <QString>
#include <DDBusInterface>
#include <QDBusPendingReply>

DNETWORKMANAGER_BEGIN_NAMESPACE

using DTK_CORE_NAMESPACE::DDBusInterface;

class DIPv4ConfigInterface : public QObject
{
    Q_OBJECT
public:
    explicit DIPv4ConfigInterface(const QByteArray &path, QObject *parent = nullptr);
    ~DIPv4ConfigInterface() override = default;

    Q_PROPERTY(QList<Config> addressData READ addressData NOTIFY addressDataChanged)
    Q_PROPERTY(QList<Config> nameserverData READ nameserverData NOTIFY nameserverDataChanged)
    Q_PROPERTY(QString gateway READ gateway NOTIFY gatewayChanged)

    QList<Config> addressData() const;
    QList<Config> nameserverData() const;
    QString gateway() const;

signals:
    void addressDataChanged(const QList<Config> &data);
    void nameserverDataChanged(const QList<Config> &data);
    void gatewayChanged(const QString &gateway);

private:
    DDBusInterface *m_inter{nullptr};
};

DNETWORKMANAGER_END_NAMESPACE

#endif
