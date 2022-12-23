// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dnetworkmanager.h"
#include "Devices"
#include "daccesspoint.h"

#include <QDebug>
#include <QCoreApplication>

DNETWORKMANAGER_USE_NAMESPACE

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    DNetworkManager manager;
    auto ret = manager.getDeviceIdList();
    if (!ret) {
        qDebug() << ret.error();
    } else {
        for (auto d : ret.value()) {
            auto ret1 = manager.getDeviceObject(d);
            if (!ret1) {
                qDebug() << ret1.error();
            } else {
                auto device = ret1.value();
                QString type;
                switch (device->deviceType()) {
                    case Dtk::NetworkManager::NMDeviceType::Generic: {
                        type = "Generic";
                        break;
                    }
                    case Dtk::NetworkManager::NMDeviceType::Ethernet:
                        type = "Wired";
                        break;
                    case Dtk::NetworkManager::NMDeviceType::WiFi:
                        type = "Wireless";
                        break;
                    case Dtk::NetworkManager::NMDeviceType::ADSL:
                        type = "Adsl";
                        break;
                    default:
                        type = "Unknown or Unsupported";
                        break;
                }
                qDebug() << type << device->managed() << device->driver();
                if (type == "Wired") {
                    auto subDevice = qobject_cast<DWiredDevice *>(device.data());
                    qDebug() << subDevice->HwAddress() << subDevice->speed();
                } else if (type == "Wireless") {
                    auto subDevice = qobject_cast<DWirelessDevice *>(device.data());
                    qDebug() << subDevice->bitrate();
                    auto ret2 = subDevice->getAllAccessPoints();
                    if (!ret2)
                        qDebug() << ret2.error();
                    else
                        qDebug() << ret2.value();
                    DAccessPoint ap(subDevice->activeAccessPoint());
                    qDebug() << ap.frequency() << ap.flags();
                }
            }
        }
    }
    return app.exec();
}
