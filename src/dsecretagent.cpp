// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dsecretagent.h"
#include "dsecretagent_p.h"

DNETWORKMANAGER_BEGIN_NAMESPACE

constexpr const char *connPath = "/org/freedesktop/NetworkManager/Settings/";

using DCORE_NAMESPACE::DUnexpected;
using DCORE_NAMESPACE::emplace_tag;

DSecretAgentPrivate::DSecretAgentPrivate(DSecretAgent *parent)
    : q_ptr(parent)
    , m_secret(new DSecretAgentInterface(this))
{
}

DSecretAgent::DSecretAgent(QObject *parent)
    : QObject(parent)
    , d_ptr(new DSecretAgentPrivate(this))
{
}

DExpected<SettingDesc> DSecretAgent::secrets(const SettingDesc &conn,
                                             const quint64 connId,
                                             const QByteArray &settingName,
                                             const QList<QByteArray> &hints,
                                             const SecretFlags &flags) const
{
    Q_D(const DSecretAgent);
    auto reply = d->m_secret->getSecrets(conn, connPath + QByteArray::number(connId), settingName, hints, flags);
    reply.waitForFinished();
    if (!reply.isValid())
        return DUnexpected{emplace_tag::USE_EMPLACE, reply.error().type(), reply.error().message()};
    return reply.value();
}

DSecretAgent::~DSecretAgent() = default;

DExpected<void> DSecretAgent::cancelSecrets(const quint64 connId, const QByteArray &settingName) const
{
    Q_D(const DSecretAgent);
    auto reply = d->m_secret->cancelGetSecrets(connPath + QByteArray::number(connId), settingName);
    reply.waitForFinished();
    if (!reply.isValid())
        return DUnexpected{emplace_tag::USE_EMPLACE, reply.error().type(), reply.error().message()};
    return {};
}

DExpected<void> DSecretAgent::saveSecret(const SettingDesc &connSettigns, const quint64 connId) const
{
    Q_D(const DSecretAgent);
    auto reply = d->m_secret->saveSecrets(connSettigns, connPath + QByteArray::number(connId));
    reply.waitForFinished();
    if (!reply.isValid())
        return DUnexpected{emplace_tag::USE_EMPLACE, reply.error().type(), reply.error().message()};
    return {};
}

DExpected<void> DSecretAgent::deleteSecret(const SettingDesc &connSettigns, const quint64 connId) const
{
    Q_D(const DSecretAgent);
    auto reply = d->m_secret->deleteSecrets(connSettigns, connPath + QByteArray::number(connId));
    reply.waitForFinished();
    if (!reply.isValid())
        return DUnexpected{emplace_tag::USE_EMPLACE, reply.error().type(), reply.error().message()};
    return {};
}

DNETWORKMANAGER_END_NAMESPACE
