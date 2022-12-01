// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DWIRELESSDEVICEINTERFACE_H
#define DWIRELESSDEVICEINTERFACE_H

#include "ddeviceInterface.h"

DNETWORKMANAGER_BEGIN_NAMESPACE

using DTK_CORE_NAMESPACE::DDBusInterface;

class DWirelessDeviceInterface : public DDeviceInterface
{
    Q_OBJECT
public:
    explicit DWirelessDeviceInterface(const QByteArray &path, QObject *parent = nullptr);
    ~DWirelessDeviceInterface() override = default;

    Q_PROPERTY(QList<QDBusObjectPath> accessPoints READ accessPoints NOTIFY accessPointsChanged)
    Q_PROPERTY(QString HwAddress READ HwAddress NOTIFY HwAddressChanged)
    Q_PROPERTY(QString permHwAddress READ permHwAddress NOTIFY permHwAddressChanged)
    Q_PROPERTY(quint32 mode READ mode NOTIFY modeChanged)
    Q_PROPERTY(quint32 bitrate READ bitrate NOTIFY bitrateChanged)
    Q_PROPERTY(QDBusObjectPath activeAccessPoint READ activeAccessPoint NOTIFY activeAccessPointChanged)
    Q_PROPERTY(quint32 wirelessCapabilities READ wirelessCapabilities NOTIFY wirelessCapabilitiesChanged)

    QList<QDBusObjectPath> accessPoints() const;
    QString HwAddress() const;
    QString permHwAddress() const;
    quint32 mode() const;
    quint32 bitrate() const;
    QDBusObjectPath activeAccessPoint() const;
    quint32 wirelessCapabilities() const;

public slots:
    QDBusPendingReply<void> requestScan(const Config &options) const;
    QDBusPendingReply<QList<QDBusObjectPath>> getAllAccessPoints() const;

signals:
    void accessPointsChanged(const QList<QDBusObjectPath> &aps);
    void HwAddressChanged(const QString &address);
    void permHwAddressChanged(const QString &address);
    void modeChanged(const quint32 mode);
    void bitrateChanged(const quint32 bitrate);
    void activeAccessPointChanged(const QDBusObjectPath &path);
    void wirelessCapabilitiesChanged(const quint32 wirelessCapabilities);

    void AccessPointAdded(const QDBusObjectPath &ap);
    void AccessPointRemoved(const QDBusObjectPath &ap);

private:
    DDBusInterface *m_wirelessInter{nullptr};
};

DNETWORKMANAGER_END_NAMESPACE

#endif
