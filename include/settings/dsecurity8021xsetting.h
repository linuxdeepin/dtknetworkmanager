// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DSECURITY8021XSETTING_H
#define DSECURITY8021XSETTING_H

#include "dnmsetting.h"

DNETWORKMANAGER_BEGIN_NAMESPACE

class DSecurity8021xSettingPrivate;

class DSecurity8021xSetting : public DNMSetting
{
public:
    enum class EapMethod {
        EapMethodUnknown = 0,
        EapMethodLeap,
        EapMethodMd5,
        EapMethodTls,
        EapMethodPeap,
        EapMethodTtls,
        EapMethodSim,
        EapMethodFast,
        EapMethodPwd,
    };

    enum class PeapVersion {
        PeapVersionUnknown = -1,
        PeapVersionZero,
        PeapVersionOne,
    };

    enum class PeapLabel {
        PeapLabelUnknown = 0,
        PeapLabelForce,
    };

    enum class FastProvisioning {
        FastProvisioningUnknown = -1,
        FastProvisioningDisabled,
        FastProvisioningAllowUnauthenticated,
        FastProvisioningAllowAuthenticated,
        FastProvisioningAllowBoth,
    };

    enum class AuthMethod {
        AuthMethodUnknown = 0,
        AuthMethodPap,
        AuthMethodChap,
        AuthMethodMschap,
        AuthMethodMschapv2,
        AuthMethodGtc,
        AuthMethodOtp,
        AuthMethodMd5,
        AuthMethodTls,
    };

    enum class AuthEapMethod {
        AuthEapMethodUnknown = 0,
        AuthEapMethodMd5,
        AuthEapMethodMschapv2,
        AuthEapMethodOtp,
        AuthEapMethodGtc,
        AuthEapMethodTls,
    };

    DSecurity8021xSetting();
    explicit DSecurity8021xSetting(const QSharedPointer<DSecurity8021xSetting> &other);
    ~DSecurity8021xSetting() override = default;

    QString name() const override;

    void setEapMethods(const QList<EapMethod> &methods);
    QList<EapMethod> eapMethods() const;

    void setIdentity(const QString &identity);
    QString identity() const;

    void setAnonymousIdentity(const QString &identity);
    QString anonymousIdentity() const;

    void setDomainSuffixMatch(const QString &domainSuffixMatch);
    QString domainSuffixMatch() const;

    void setPacFile(const QString &filePath);
    QString pacFile() const;

    void setCaCertificate(const QByteArray &certificate);
    QByteArray caCertificate() const;

    void setCaPath(const QString &path);
    QString caPath() const;

    void setSubjectMatch(const QString &substring);
    QString subjectMatch() const;

    void setAltSubjectMatches(const QStringList &strings);
    QStringList altSubjectMatches() const;

    void setClientCertificate(const QByteArray &certificate);
    QByteArray clientCertificate() const;

    void setPhase1PeapVersion(PeapVersion version);
    PeapVersion phase1PeapVersion() const;

    void setPhase1PeapLabel(PeapLabel label);
    PeapLabel phase1PeapLabel() const;

    void setPhase1FastProvisioning(FastProvisioning provisioning);
    FastProvisioning phase1FastProvisioning() const;

    void setPhase2AuthMethod(AuthMethod method);
    AuthMethod phase2AuthMethod() const;

    void setPhase2AuthEapMethod(AuthEapMethod method);
    AuthEapMethod phase2AuthEapMethod() const;

    void setPhase2CaCertificate(const QByteArray &certificate);
    QByteArray phase2CaCertificate() const;

    void setPhase2CaPath(const QString &path);
    QString phase2CaPath() const;

    void setPhase2SubjectMatch(const QString &substring);
    QString phase2SubjectMatch() const;

    void setPhase2AltSubjectMatches(const QStringList &strings);
    QStringList phase2AltSubjectMatches() const;

    void setPhase2ClientCertificate(const QByteArray &certificate);
    QByteArray phase2ClientCertificate() const;

    void setPassword(const QString &password);
    QString password() const;

    void setPasswordFlags(DNMSetting::SecretFlags flags);
    DNMSetting::SecretFlags passwordFlags() const;

    void setPasswordRaw(const QByteArray &password);
    QByteArray passwordRaw() const;

    void setPasswordRawFlags(DNMSetting::SecretFlags flags);
    DNMSetting::SecretFlags passwordRawFlags() const;

    void setPrivateKey(const QByteArray &key);
    QByteArray privateKey() const;

    void setPrivateKeyPassword(const QString &password);
    QString privateKeyPassword() const;

    void setPrivateKeyPasswordFlags(DNMSetting::SecretFlags flags);
    DNMSetting::SecretFlags privateKeyPasswordFlags() const;

    void setPhase2PrivateKey(const QByteArray &key);
    QByteArray phase2PrivateKey() const;

    void setPhase2PrivateKeyPassword(const QString &password);
    QString phase2PrivateKeyPassword() const;

    void setPhase2PrivateKeyPasswordFlags(DNMSetting::SecretFlags flags);
    DNMSetting::SecretFlags phase2PrivateKeyPasswordFlags() const;

    void setPin(const QString &pin);
    QString pin() const;

    void setPinFlags(DNMSetting::SecretFlags flags);
    DNMSetting::SecretFlags pinFlags() const;

    void setSystemCaCertificates(bool use);
    bool systemCaCertificates() const;

    QStringList needSecrets(bool requestNew = false) const override;

    void fromMap(const QVariantMap &setting) override;
    QVariantMap toMap() const override;

    QVariantMap secretsToMap() const override;
    void mapToSecrets(const QVariantMap &secrets) override;

protected:
    QScopedPointer<DSecurity8021xSettingPrivate> d_ptr;

private:
    Q_DECLARE_PRIVATE(DSecurity8021xSetting)
};

DNETWORKMANAGER_END_NAMESPACE

#endif
