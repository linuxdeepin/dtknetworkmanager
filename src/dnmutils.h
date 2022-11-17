// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DNMUTILS_H
#define DNMUTILS_H

#include "dnetworkmanager_global.h"
#include <QDBusObjectPath>

DNETWORKMANAGER_BEGIN_NAMESPACE

inline quint64 getIdFromObjectPath(const QDBusObjectPath &path)
{
    const auto &strId = path.path().split("/").last();
    bool ok;
    auto intId = strId.toLongLong(&ok);
    return ok ? intId : 0;
}

DNETWORKMANAGER_END_NAMESPACE

#endif
