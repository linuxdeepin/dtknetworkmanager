// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DACCESSPOINTINTERFACE_H
#define DACCESSPOINTINTERFACE_H

#include "dnetworkmanager_global.h"
#include "dnetworkmanagertypes.h"
#include <DDBusInterface>
#include <QSharedPointer>
#include <QDBusPendingReply>
#include <QString>
#include <QMap>
#include <QVariant>
#include <QList>

DNETWORKMANAGER_BEGIN_NAMESPACE

using DTK_CORE_NAMESPACE::DDBusInterface;

class DAccessPointInterface : public QObject
{
    Q_OBJECT
public:
    explicit DAccessPointInterface(const QByteArray &path, QObject *parent = nullptr);
    ~DAccessPointInterface() override = default;

    Q_PROPERTY(QString SSID READ SSID NOTIFY SSIDChanged)
    Q_PROPERTY(quint8 strength READ strength NOTIFY strengthChanged)
    Q_PROPERTY(quint32 flags READ flags NOTIFY flagsChanged)
    Q_PROPERTY(quint32 frequency READ frequency NOTIFY frequencyChanged)
    Q_PROPERTY(quint32 rsnFlags READ rsnFlags NOTIFY rsnFlagsChanged)
    Q_PROPERTY(quint32 wpaFlags READ wpaFlags NOTIFY wpaFlagsChanged)

    QString SSID() const;
    quint8 strength() const;
    quint32 flags() const;
    quint32 frequency() const;
    quint32 rsnFlags() const;
    quint32 wpaFlags() const;

signals:

    void SSIDChanged(const QString &ssid);
    void strengthChanged(const quint8 strength);
    void frequencyChanged(const quint32 frequency);
    void flagsChanged(const quint32 flags);
    void rsnFlagsChanged(const quint32 rsnFlags);
    void wpaFlagsChanged(const quint32 wpaFlags);

private:
    DDBusInterface *m_inter{nullptr};
};

DNETWORKMANAGER_END_NAMESPACE

#endif
