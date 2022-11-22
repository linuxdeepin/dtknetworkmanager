// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DCONNECTIONSETTING_H
#define DCONNECTIONSETTING_H

#include "dnetworkmanagertypes.h"
#include <DExpected>
#include <QUrl>

DNETWORKMANAGER_BEGIN_NAMESPACE

class DConnectionSettingPrivate;

using DCORE_NAMESPACE::DExpected;

class DConnectionSetting : public QObject
{
    Q_OBJECT
public:
    Q_DECLARE_FLAGS(NMSCFlags, NMSettingsConnectionFlags);

    explicit DConnectionSetting(const quint64 id, QObject *parent = nullptr);
    ~DConnectionSetting() = default;

    Q_PROPERTY(bool unsaved READ unsaved NOTIFY unsavedChanged)
    Q_PROPERTY(QUrl filename READ filename NOTIFY filenameChanged)
    Q_PROPERTY(NMSCFlags flags READ flags NOTIFY flagsChanged)

    bool unsaved() const;
    QUrl filename() const;
    NMSCFlags flags() const;

public slots:
    DExpected<void> updateSetting(const SettingDesc &settings) const;
    DExpected<void> deleteSetting() const;
    DExpected<SettingDesc> settings() const;

signals:
    void unsavedChanged(const bool unsaved);
    void filenameChanged(const QUrl &filename);
    void flagsChanged(const NMSCFlags flags);
    void Removed();
    void Updated();

private:
    QScopedPointer<DConnectionSettingPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DConnectionSetting)
};

Q_DECLARE_OPERATORS_FOR_FLAGS(DConnectionSetting::NMSCFlags)

DNETWORKMANAGER_END_NAMESPACE

#endif
