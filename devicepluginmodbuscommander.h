/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Copyright (C) 2019 Bernhard Trinnes <bernhard.trinnes@nymea.io>        *
 *                                                                         *
 *  This file is part of nymea.                                            *
 *                                                                         *
 *  This library is free software; you can redistribute it and/or          *
 *  modify it under the terms of the GNU Lesser General Public             *
 *  License as published by the Free Software Foundation; either           *
 *  version 2.1 of the License, or (at your option) any later version.     *
 *                                                                         *
 *  This library is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      *
 *  Lesser General Public License for more details.                        *
 *                                                                         *
 *  You should have received a copy of the GNU Lesser General Public       *
 *  License along with this library; If not, see                           *
 *  <http://www.gnu.org/licenses/>.                                        *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef DEVICEPLUGINMODBUSCOMMANDER_H
#define DEVICEPLUGINMODBUSCOMMANDER_H

#include "devices/deviceplugin.h"
#include "devices/devicemanager.h"
#include "plugintimer.h"
#include "modbustcpmaster.h"
#include "modbusrtumaster.h"

#include <QSerialPortInfo>

class DevicePluginModbusCommander : public DevicePlugin
{
    Q_OBJECT

    Q_PLUGIN_METADATA(IID "io.nymea.DevicePlugin" FILE "devicepluginmodbuscommander.json")
    Q_INTERFACES(DevicePlugin)

public:
    explicit DevicePluginModbusCommander();

    void init() override;
    void discoverDevices(DeviceDiscoveryInfo *info) override;
    void setupDevice(DeviceSetupInfo *info) override;
    void postSetupDevice(Device *device) override;
    void executeAction(DeviceActionInfo *info) override;
    void deviceRemoved(Device *device) override;

private:
    PluginTimer *m_refreshTimer = nullptr;

    QHash<Device *, ModbusRTUMaster *> m_modbusRTUMasters;
    QHash<Device *, ModbusTCPMaster *> m_modbusTCPMasters;

    void readRegister(Device *device);
    void writeRegister(Device *device, Action action);

private slots:
    void onRefreshTimer();

    void onPluginConfigurationChanged(const ParamTypeId &paramTypeId, const QVariant &value);

    void onConnectionStateChanged(bool status);
    void onReceivedCoil(quint32 slaveAddress, quint32 modbusRegister, bool value);
    void onReceivedDiscreteInput(quint32 slaveAddress, quint32 modbusRegister, bool value);
    void onReceivedHoldingRegister(quint32 slaveAddress, quint32 modbusRegister, int value);
    void onReceivedInputRegister(quint32 slaveAddress, quint32 modbusRegister, int value);
};

#endif // DEVICEPLUGINMODBUSCOMMANDER_H
