// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DNETWORKMANAGERTYPES_H
#define DNETWORKMANAGERTYPES_H
#include "dnetworkmanager_global.h"
#include <QMap>
#include <QScopedPointer>
#include <QString>
#include <QVariant>

DNETWORKMANAGER_BEGIN_NAMESPACE

using Config = QMap<QString, QVariant>;
using SettingDesc = QMap<QString, Config>;

// custom enum

enum class NMState : quint8 {
    NMStateUnknown = 0,
    NMStateAsleep = 10,
    NMStateDisconnected = 20,
    NMStateDisconnecting = 30,
    NMStateConnecting = 40,
    NMStateConnectedLocal = 50,
    NMStateConnectedSite = 60,
    NMStateConnectedGlobal = 70
};

enum class NMConnectivityState : quint8 {
    NMConnectivityUnknown = 0,
    NMConnectivityNone,
    NMConnectivityPortal,
    NMConnectivityLimited,
    NMConnectivityFull
};

enum class NMActiveConnectionState : quint8 {
    NMActiveConnectionStateUnknown = 0,
    NMActiveConnectionStateActivating,
    NMActiveConnectionStateActivated,
    NMActiveConnectionStateDeactivating,
    NMActiveConnectionStateDeactivated
};

enum class NMActiveConnectionStateReason : quint8 {
    NMActiveConnectionStateReasonUnknown = 0,
    NMActiveConnectionStateReasonNone,
    NMActiveConnectionStateReasonUserDisconnected,
    NMActiveConnectionStateReasonDeviceDisconnected,
    NMActiveConnectionStateReasonServiceStopped,
    NMActiveConnectionStateReasonIPConfigInvalid,
    NMActiveConnectionStateReasonConnectTimeout,
    NMActiveConnectionStateReasonServiceStartTimeout,
    NMActiveConnectionStateReasonServiceStartFailed,
    NMActiveConnectionStateReasonNoSecrets,
    NMActiveConnectionStateReasonLoginFailed,
    NMActiveConnectionStateReasonConnectionRemoved,
    NMActiveConnectionStateReasonDependencyFailed,
    NMActiveConnectionStateReasonDeviceRealizeFailed,
    NMActiveConnectionStateReasonDeviceRemoved
};

enum class NMVpnConnectionState : quint8 {
    NMVpnConnectionStateUnknown = 0,
    NMVpnConnectionStatePrepare,
    NMVpnConnectionStateNeedAuth,
    NMVpnConnectionStateConnect,
    NMVpnConnectionStateIPConfigGet,
    NMVpnConnectionStateActivated,
    NMVpnConnectionStateFailed,
    NMVpnConnectionStateDisconnected
};

enum class NM80211ApFlags : quint8 {
    NM80211ApFlagsNone = 0,
    NM80211ApFlagsPrivacy,
    NM80211ApFlagsWPS,
    NM80211ApFlagsWPSPBC = 4,
    NM80211ApFlagsWPSPIN = 8
};

enum class NM80211ApSecurityFlags : quint16 {
    NM80211ApSecNone = 0x0,
    NM80211ApSecPairWEP40,
    NM80211ApSecPairWEP104,
    NM80211ApSecPairTKIP = 0x4,
    NM80211ApSecPairCCMP = 0x8,
    NM80211ApSecGroupWEP40 = 0x10,
    NM80211ApSecGroupWEP104 = 0x20,
    NM80211ApSecGroupTKIP = 0x40,
    NM80211ApSecGroupCCMP = 0x80,
    NM80211ApSecKeyMgmtPsk = 0x100,
    NM80211ApSecKeyMgmt8021X = 0x200
};

enum class NMSettingsConnectionFlags : quint8 {
    NMSettingsConnectionFlagNone = 0,
    NMSettingsConnectionFlagFlagUnsaved,
    NMSettingsConnectionFlagNMGenerated,
    NMSettingsConnectionFlagVolatile = 4
};

enum class ProxyType : quint8 { ProxyTypeHTTP = 0, ProxyTypeSocks4, ProxyTypeSocks5 };

enum class SystemProxyMethod : quint8 { SystemProxyMethodNone = 0, SystemProxyMethodManual, SystemProxyMethodAuto };

enum class NMDeviceType : quint8 {
    NMDeviceTypeUnknown = 0,
    NMDeviceTypeGeneric,
    NMDeviceTypeEthernet,
    NMDeviceTypeWiFi,
    NMDeviceTypeUnused1,
    NMDeviceTypeUnused2,
    NMDeviceTypeBT,
    NMDeviceTypeOLPCMesh,
    NMDeviceTypeWiMAX,
    NMDeviceTypeModem,
    NMDeviceTypeInfiniBand,
    NMDeviceTypeBond,
    NMDeviceTypeVLAN,
    NMDeviceTypeADSL,
    NMDeviceTypeBridge,
    NMDeviceTypeTeam,
    NMDeviceTypeTun,
    NMDeviceTypeIPTunnel,
    NMDeviceTypeMACVLAN,
    NMDeviceTypeVXLAN,
    NMDeviceTypeVEth,
    NMDeviceTypeMACSec,
    NMDeviceTypeDummy,
    NMDeviceTypePPP,
    NMDeviceTypeOVSInterface,
    NMDeviceTypeOVSPort,
    NMDeviceTypeOVSBridge,
    NMDeviceTypeWPAN,
    NMDeviceType6LoWPAN,
    NMDeviceTypeWireGuard
};

enum class NMDeviceInterfaceFlags : quint32 {
    NMDeviceInterfaceFlagNone = 0x0,
    NMDeviceInterfaceFlagUP,
    NMDeviceInterfaceFlagLowerUP,
    NMDeviceInterfaceFlagCarrier = 0x10000
};

enum class NMDeviceState : quint8 {
    NMDeviceStateUnknown = 0,
    NMDeviceStateUnmanaged = 10,
    NMDeviceStateUnavailable = 20,
    NMDeviceStateDisconnected = 30,
    NMDeviceStatePrepare = 40,
    NMDeviceStateConfig = 50,
    NMDeviceStateNeedAuth = 60,
    NMDeviceStateIPConfig = 70,
    NMDeviceStateIPCheck = 80,
    NMDeviceStateSecondaries = 90,
    NMDeviceStateActivated = 100,
    NMDeviceStateDeactivated = 110,
    NMDeviceStateFailed = 120
};

enum class NMDeviceStateReason : quint8 {
    NMDeviceStateReasonNone = 0,
    NMDeviceStateReasonUnknown,
    NMDeviceStateReasonNowManaged,
    NMDeviceStateReasonNowUnmanaged,
    NMDeviceStateReasonConfigFailed,
    NMDeviceStateReasonIPConfigUnavailable,
    NMDeviceStateReasonIPConfigExpired,
    NMDeviceStateReasonNoSecret,
    NMDeviceStateReasonSupplicantDisconnected,
    NMDeviceStateReasonSupplicantConfigFailed,
    NMDeviceStateReasonSupplicantFailed,
    NMDeviceStateReasonSupplicantTimeout,
    NMDeviceStateReasonPPPStartFailed,
    NMDeviceStateReasonPPPDisconnect,
    NMDeviceStateReasonPPPFailed,
    NMDeviceStateReasonDHCPStartFailed,
    NMDeviceStateReasonDHCPError,
    NMDeviceStateReasonDHCPFailed,
    NMDeviceStateReasonSharedStartFailed,
    NMDeviceStateReasonSharedFailed,
    NMDeviceStateReasonAutoIPStartFailed,
    NMDeviceStateReasonAutoIPError,
    NMDeviceStateReasonAutoIPFailed,
    NMDeviceStateReasonModemBusy,
    NMDeviceStateReasonModemNoDialTone,
    NMDeviceStateReasonModemNoCarrier,
    NMDeviceStateReasonModemDialTimeout,
    NMDeviceStateReasonModemDialFailed,
    NMDeviceStateReasonModemInitFailed,
    NMDeviceStateReasonGSMAPNFailed,
    NMDeviceStateReasonGSMRegistrationNotSearching,
    NMDeviceStateReasonGSMRegistrationDenied,
    NMDeviceStateReasonGSMRegistrationTimeout,
    NMDeviceStateReasonGSMRegistrationFailed,
    NMDeviceStateReasonGSMPINCheckFailed,
    NMDeviceStateReasonFirmwareMissing,
    NMDeviceStateReasonRemoved,
    NMDeviceStateReasonSleeping,
    NMDeviceStateReasonConnectionRemoved,
    NMDeviceStateReasonUserRequested,
    NMDeviceStateReasonCarrier,
    NMDeviceStateReasonConnectionAssumed,
    NMDeviceStateReasonSupplicantAvailable,
    NMDeviceStateReasonModemNotFound,
    NMDeviceStateReasonBTFailed,
    NMDeviceStateReasonGSMSIMPINRequired,
    NMDeviceStateReasonGSMSIMPUKRequired,
    NMDeviceStateReasonGSMSIMWrong,
    NMDeviceStateReasonInfinibandMode,
    NMDeviceStateReasonDependencyFailed,
    NMDeviceStateReasonBR2684Failed,
    NMDeviceStateReasonModemManagerUnavailable,
    NMDeviceStateReasonSSIDNotFound,
    NMDeviceStateReasonSecondaryConnectionFailed,
    NMDeviceStateReasonDCBFCoEFailed,
    NMDeviceStateReasonTeamdControlFailed,
    NMDeviceStateReasonModemFailed,
    NMDeviceStateReasonModemAvailable,
    NMDeviceStateReasonGSMSIMPINIncorrect,
    NMDeviceStateReasonNewActivation,
    NMDeviceStateReasonParentChanged,
    NMDeviceStateReasonParentManagedChanged,
    NMDeviceStateReasonOVSDBFailed,
    NMDeviceStateReasonIPAddressDuplicate,
    NMDeviceStateReasonIPMethodUnsupported,
    NMDeviceStateReasonSRIOVConfigurationFailed,
    NMDeviceStateReasonPeerNotFound
};

enum class NM80211Mode : quint8 { NM80211ModeUnknown, NM80211ModeAdHoc, NM80211ModeInfra, NM80211ModeAP };

enum class NMDeviceWiFiCapabilities : quint16 {
    NMDeviceWiFiCapNone = 0x0,
    NMDeviceWiFiCapCipherWEP40,
    NMDeviceWiFiCapCipherWEP104,
    NMDeviceWiFiCapCipherTKIP = 0x4,
    NMDeviceWiFiCapCipherCCMP = 0x8,
    NMDeviceWiFiCapWPA = 0x10,
    NMDeviceWiFiCapRSN = 0x20,
    NMDeviceWiFiCapAP = 0x40,
    NMDeviceWiFiCapAdHoc = 0x80,
    NMDeviceWiFiCapFreqValid = 0x100,
    NMDeviceWiFiCapFreq2GHz = 0x200,
    NMDeviceWiFiCapFreq5GHz = 0x400
};

enum class NMSecretAgentCapabilities : quint8 { NMSecretAgentCapabilityNone = 0, NMSecretAgentCapabilityVPNHints };

enum class NMSecretAgentGetSecretsFlags : quint32 {
    NMSecretAgentGetSecretsFlagNone = 0x0,
    NMSecretAgentGetSecretsFlagAllowInteraction,
    NMSecretAgentGetSecretsFlagRequestNew,
    NMSecretAgentGetSecretsFlagUserRequested = 0x4,
    NMSecretAgentGetSecretsFlagWPSPBCActive = 0x8,
    NMSecretAgentGetSecretsFlagOnlySystem = 0x80000000,
    NMSecretAgentGetSecretsFlagNoError = 0x40000000
};

// custom structure

struct NewConn
{
    quint64 settingId;
    quint64 activeConnId;
};

struct SystemProxyAddr
{
    quint32 port;
    QString host;
};

struct AppProxySet
{
    quint32 port;
    ProxyType type;
    QByteArray ip;
    QByteArray password;
    QString user;
};

DNETWORKMANAGER_END_NAMESPACE

#endif
