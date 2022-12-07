// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dagentmanager.h"
#include "dagentmanager_p.h"

DNETWORKMANAGER_BEGIN_NAMESPACE

using DCORE_NAMESPACE::DUnexpected;
using DCORE_NAMESPACE::emplace_tag;

DAgentManagerPrivate::DAgentManagerPrivate(DAgentManager *parent)
    : q_ptr(parent)
    , m_agent(new DAgentManagerInterface(this))
{
}

DAgentManager::DAgentManager(QObject *parent)
    : QObject(parent)
    , d_ptr(new DAgentManagerPrivate(this))
{
}

DAgentManager::~DAgentManager() = default;

DExpected<void> DAgentManager::registerAgent(const QByteArray &identifier) const
{
    Q_D(const DAgentManager);
    auto reply = d->m_agent->registerAgent(identifier);
    reply.waitForFinished();
    if (!reply.isValid())
        return DUnexpected{emplace_tag::USE_EMPLACE, reply.error().type(), reply.error().message()};
    return {};
}

DExpected<void> DAgentManager::registerWithCapabilities(const QByteArray &identifier, const NMSecretAgentCapabilities caps) const
{
    Q_D(const DAgentManager);
    auto reply = d->m_agent->registerWithCapabilities(identifier, caps);
    reply.waitForFinished();
    if (!reply.isValid())
        return DUnexpected{emplace_tag::USE_EMPLACE, reply.error().type(), reply.error().message()};
    return {};
}

DExpected<void> DAgentManager::unregisterAgent() const
{
    Q_D(const DAgentManager);
    auto reply = d->m_agent->unregisterAgent();
    reply.waitForFinished();
    if (!reply.isValid())
        return DUnexpected{emplace_tag::USE_EMPLACE, reply.error().type(), reply.error().message()};
    return {};
}

DNETWORKMANAGER_END_NAMESPACE
