// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DSECRETAGENT_P_H
#define DSECRETAGENT_P_H

#include "dbus/dsecretagentinterface.h"

DNETWORKMANAGER_BEGIN_NAMESPACE

class DSecretAgent;

class DSecretAgentPrivate : public QObject
{
    Q_OBJECT
public:
    explicit DSecretAgentPrivate(DSecretAgent *parent);
    ~DSecretAgentPrivate() = default;

    DSecretAgent *q_ptr{nullptr};
    DSecretAgentInterface *m_secret{nullptr};
    Q_DECLARE_PUBLIC(DSecretAgent)
};

DNETWORKMANAGER_END_NAMESPACE

#endif
