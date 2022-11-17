// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DNETWORKMANAGER_P_H
#define DNETWORKMANAGER_P_H

#include "dbus/dnetworkmanagerinterface.h"

DNETWORKMANAGER_BEGIN_NAMESPACE

class DNetworkManager;

class DNetworkManagerPrivate : public QObject
{
    Q_OBJECT
public:
    explicit DNetworkManagerPrivate(DNetworkManager *parent = nullptr);
    ~DNetworkManagerPrivate() = default;

    DNetworkManager *q_ptr{nullptr};
    DNetworkManagerInterface *m_manager{nullptr};
    Q_DECLARE_PUBLIC(DNetworkManager)
};
DNETWORKMANAGER_END_NAMESPACE
#endif
