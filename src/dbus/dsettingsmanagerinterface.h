// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DSETTINGSMANAGERINTERFACE_H
#define DSETTINGSMANAGERINTERFACE_H

#include "dnetworkmanager_global.h"
#include "dnetworkmanagertypes.h"
#include <DDBusInterface>
#include <QDBusPendingReply>
#include <QString>

DNETWORKMANAGER_BEGIN_NAMESPACE

using DTK_CORE_NAMESPACE::DDBusInterface;

class DSettingsManagerInterface : public QObject
{
    Q_OBJECT
public:
    explicit DSettingsManagerInterface(QObject *parent = nullptr);
    ~DSettingsManagerInterface() = default;

public slots:
    QDBusPendingReply<QList<QDBusObjectPath>> listConnections() const;
    QDBusPendingReply<QDBusObjectPath> getConnectionByUUID(const QByteArray &UUID) const;
    QDBusPendingReply<QDBusObjectPath> addConnection(const SettingDesc &conn) const;

private:
    DDBusInterface *m_inter{nullptr};
};

DNETWORKMANAGER_END_NAMESPACE

#endif
