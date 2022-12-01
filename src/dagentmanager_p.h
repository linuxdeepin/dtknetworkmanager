// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DAGENTMANAGER_P_H
#define DAGENTMANAGER_P_H

#include "dbus/dagentmanagerinterface.h"

DNETWORKMANAGER_BEGIN_NAMESPACE

class DAgentManager;

class DAgentManagerPrivate : public QObject
{
    Q_OBJECT
public:
    explicit DAgentManagerPrivate(DAgentManager *parent = nullptr);
    ~DAgentManagerPrivate() override = default;

    DAgentManager *q_ptr{nullptr};
    DAgentManagerInterface *m_agent{nullptr};
    Q_DECLARE_PUBLIC(DAgentManager)
};

DNETWORKMANAGER_END_NAMESPACE

#endif
