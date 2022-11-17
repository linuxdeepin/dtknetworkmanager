// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DAGENTMANAGER_H
#define DAGENTMANAGER_H

#include <DExpected>
#include "dnetworkmanagertypes.h"

DNETWORKMANAGER_BEGIN_NAMESPACE

class DAgentManagerPrivate;

using DCORE_NAMESPACE::DExpected;

class DAgentManager : public QObject
{
    Q_OBJECT
public:
    explicit DAgentManager(QObject *parent = nullptr);
    ~DAgentManager() = default;

public slots:
    DExpected<void> registerAgent(const QByteArray &identifier) const;
    DExpected<void> registerWithCapabilities(const QByteArray &identifier, const NMSecretAgentCapabilities caps) const;
    DExpected<void> unregister() const;

private:
    QScopedPointer<DAgentManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DAgentManager)
};

DNETWORKMANAGER_END_NAMESPACE

#endif
