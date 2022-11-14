// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DAPPPROXYINTERFACE_H
#define DAPPPROXYINTERFACE_H

#include "dnetworkmanager_global.h"
#include <QObject>
#include <QString>
#include <DDBusInterface>
#include <QDBusPendingReply>

DNETWORKMANAGER_BEGIN_NAMESPACE

using DTK_CORE_NAMESPACE::DDBusInterface;

class DAppProxyInterface : public QObject
{
    Q_OBJECT
public:
    explicit DAppProxyInterface(QObject *parent = nullptr);
    ~DAppProxyInterface() = default;

    Q_PROPERTY(QString IP READ IP NOTIFY IPChanged)
    Q_PROPERTY(QString password READ password NOTIFY passwordChanged)
    Q_PROPERTY(QString type READ type NOTIFY typeChanged)
    Q_PROPERTY(QString user READ user NOTIFY userChanged)
    Q_PROPERTY(quint32 port READ port NOTIFY portChanged)

    QString IP() const;
    QString password() const;
    QString type() const;
    QString user() const;
    quint32 port() const;

public slots:
    QDBusPendingReply<void>
    set(const QString &type, const QString &ip, const quint32 port, const QString &user, const QString &password) const;

signals:
    void IPChanged(const QString &ip);
    void passwordChanged(const QString &password);
    void typeChanged(const QString &type);
    void userChanged(const QString &user);
    void portChanged(const quint32 port);

private:
    DDBusInterface *m_inter{nullptr};
};

DNETWORKMANAGER_END_NAMESPACE

#endif
