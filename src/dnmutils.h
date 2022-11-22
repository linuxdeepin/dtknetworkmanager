// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DNMUTILS_H
#define DNMUTILS_H

#include "dnetworkmanager_global.h"
#include "dnetworkmanagertypes.h"
#include <QDBusObjectPath>

DNETWORKMANAGER_BEGIN_NAMESPACE

inline quint64 getIdFromObjectPath(const QDBusObjectPath &path)
{
    const auto &strId = path.path().split("/").last();
    bool ok;
    auto intId = strId.toLongLong(&ok);
    return ok ? intId : 0;
}

inline const char *enumToProxyType(const ProxyType type)
{
    switch (type) {
        case ProxyType::ProxyTypeHTTP:
            return "http";
        case ProxyType::ProxyTypeSocks4:
            return "socks4";
        case ProxyType::ProxyTypeSocks5:
            return "socks5";
    }
    Q_UNREACHABLE();
}

inline ProxyType proxyTypeToEnum(const QString &type)
{
    if (type == "http")
        return ProxyType::ProxyTypeHTTP;
    else if (type == "socks4")
        return ProxyType::ProxyTypeSocks4;
    else if (type == "socks5")
        return ProxyType::ProxyTypeSocks5;
    Q_UNREACHABLE();
}

inline SystemProxyMethod proxyMethodToEnum(const QString &method)
{
    if (method == "auto")
        return SystemProxyMethod::SystemProxyMethodAuto;
    else if (method == "manual")
        return SystemProxyMethod::SystemProxyMethodManual;
    else if (method == "none")
        return SystemProxyMethod::SystemProxyMethodNone;
    Q_UNREACHABLE();
}

inline const char *enumToProxyMethod(const SystemProxyMethod method)
{
    switch (method) {
        case SystemProxyMethod::SystemProxyMethodAuto:
            return "auto";
        case SystemProxyMethod::SystemProxyMethodManual:
            return "manual";
        case SystemProxyMethod::SystemProxyMethodNone:
            return "none";
    }
    Q_UNREACHABLE();
}

DNETWORKMANAGER_END_NAMESPACE

#endif
