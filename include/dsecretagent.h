// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DSECRETAGENT_H
#define DSECRETAGENT_H

#include <DExpected>
#include "dnetworkmanagertypes.h"
#include <QFlags>

DNETWORKMANAGER_BEGIN_NAMESPACE

class DSecretAgentPrivate;

using DCORE_NAMESPACE::DExpected;

class DSecretAgent : public QObject
{
    Q_OBJECT
public:
    explicit DSecretAgent(QObject *parent = nullptr);
    ~DSecretAgent() = default;

    Q_DECLARE_FLAGS(SecretFlags, NMSecretAgentGetSecretsFlags);

public slots:
    DExpected<SettingDesc> secrets(const SettingDesc &conn,
                                   const QByteArray &UUID,
                                   const QByteArray &settingName,
                                   const QList<QByteArray> &hints,
                                   const SecretFlags &flags) const;
    DExpected<void> cancelSecrets(const QByteArray &UUID, const QByteArray &settingName) const;
    DExpected<void> saveSecret(const SettingDesc &connSettigns, const QByteArray &UUID) const;
    DExpected<void> deleteSecret(const SettingDesc &connSettigns, const QByteArray &UUID) const;

private:
    QScopedPointer<DSecretAgentPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DSecretAgent)
};

Q_DECLARE_OPERATORS_FOR_FLAGS(DSecretAgent::SecretFlags)

DNETWORKMANAGER_END_NAMESPACE

#endif
