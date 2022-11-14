// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DAGENTMANAGERINTERFACE_H
#define DAGENTMANAGERINTERFACE_H

#include "dnetworkmanagertypes.h"
#include "dnetworkmanager_global.h"
#include <QObject>
#include <QString>
#include <DDBusInterface>
#include <QDBusPendingReply>

DNETWORKMANAGER_BEGIN_NAMESPACE

using DTK_CORE_NAMESPACE::DDBusInterface;

class DAgentManagerInterface : public QObject
{
    Q_OBJECT
public:
    explicit DAgentManagerInterface(QObject *parent = nullptr);
    ~DAgentManagerInterface() = default;

public slots:

    QDBusPendingReply<void> registerAgent(const QByteArray &identifier) const;
    QDBusPendingReply<void> registerWithCapabilities(const QByteArray &identifier, const NMSecretAgentCapabilities cap) const;
    QDBusPendingReply<void> unregisterAgent() const;

private:
    DDBusInterface *m_inter{nullptr};
};

DNETWORKMANAGER_END_NAMESPACE

#endif
