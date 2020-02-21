/*
 * Copyright (c) 2019, Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#if MBED_CONF_SIMCOM_SIM7020_PROVIDE_DEFAULT
#include "SIMCOM_SIM7020.h"
#include "UARTSerial.h"

using namespace mbed;

CellularDevice *CellularDevice::get_default_instance()
{
    static UARTSerial serial(MBED_CONF_SIMCOM_SIM7020_TX, MBED_CONF_SIMCOM_SIM7020_RX, MBED_CONF_SIMCOM_SIM7020_BAUDRATE);
#if defined (MBED_CONF_SIMCOM_SIM7020_RTS) && defined(MBED_CONF_SIMCOM_SIM7020_CTS)
    tr_debug("SIMCOM_SIM7020 flow control: RTS %d CTS %d", MBED_CONF_SIMCOM_SIM7020_RTS, MBED_CONF_SIMCOM_SIM7020_CTS);
    serial.set_flow_control(SerialBase::RTSCTS, MBED_CONF_SIMCOM_SIM7020_RTS, MBED_CONF_SIMCOM_SIM7020_CTS);
#endif
    static SIMCOM_SIM7020 device(&serial);
    return &device;
#endif
}
