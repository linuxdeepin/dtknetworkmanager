// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DDHCP4CONFIG_H
#define DDHCP4CONFIG_H

#include "dnetworkmanager_global.h"
#include "dnetworkmanagertypes.h"
#include <QObject>
#include <QString>
#include <DDBusInterface>

DNETWORKMANAGER_BEGIN_NAMESPACE

using DTK_CORE_NAMESPACE::DDBusInterface;

class DDHCP6ConfigInterface : public QObject
{
    Q_OBJECT
public:
    explicit DDHCP6ConfigInterface(const QByteArray &path, QObject *parent = nullptr);
    ~DDHCP6ConfigInterface() = default;

    Q_PROPERTY(Config options READ options NOTIFY optionsChanged)

    Config options() const;

signals:
    void optionsChanged(const Config &option);

private:
    DDBusInterface *m_inter{nullptr};
};

DNETWORKMANAGER_END_NAMESPACE
#endif
