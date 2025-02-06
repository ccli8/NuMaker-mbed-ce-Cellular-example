This example is modified from [mbed-os-example-cellular](https://github.com/ARMmbed/mbed-os-example-cellular).

Before build the example, please notice

1. For NB-IoT and Cat M1, please contact your service provider to get band information and use AT command to setup it.

   For Taiwan example, it uses the band 1, 3, 8 and 28, you can refer the AT command document to do it.
   1a. In BG96 case, you need to type below AT command to set band.
         AT+QCFG="band",0,8000085,8000085,1
       And after first time to register network, you still need type below AT command to save information.
         AT+CFUN=0
   1b. In SIM7020 case, you need to type below AT command to set band.
         AT+CBAND=1,3,8,28

   For Taiwan's CHT ISP example, it uses the Band 8, you can only set band 8 active.

2. If run SIM7020, please use Mbed-OS 5.15.0 and later.

3. Add the cellular device support in mbed_app.json as below.

   For SIMCOM SIM7020, please add the first two configurations. The drivers.uart-serial-rxbuf-size should be MAX_PACKET_SIZE*2+100.
    "target_overrides": {
        "*": {
            "target.extra_labels_add": ["SIM7020"],
            "SIMCOM_SIM7020.provide-default": true,
            "SIMCOM_SIM7020.tx": "D1",
            "SIMCOM_SIM7020.rx": "D0",
            "drivers.uart-serial-rxbuf-size": 4196,
            "target.network-default-interface-type": "CELLULAR",
            ...
            "lwip.ppp-enabled": false,
            "lwip.tcp-enabled": false,

   For QUECTEL BG96, please add the first three configurations.
    "target_overrides": {
        "*": {
            "QUECTEL_BG96.provide-default": true,
            "QUECTEL_BG96.tx": "D1",
            "QUECTEL_BG96.rx": "D0",
            "target.network-default-interface-type": "CELLULAR",
            ...
            "lwip.ppp-enabled": false,
            "lwip.tcp-enabled": false,

   For QUECTEL EC2x, please add the first three configurations.
    "target_overrides": {
        "*": {
            "GENERIC_AT3GPP.provide-default": true,
            "GENERIC_AT3GPP.tx": "D1",
            "GENERIC_AT3GPP.rx": "D0",
            "target.network-default-interface-type": "CELLULAR",
            ...
            "lwip.ppp-enabled": true,
            "lwip.tcp-enabled": true,

4. Add the cellular network APN support in mbed_app.json.

For other configurations, you can refer the original README content as below.


====================================================================================================


# Example cellular application for Mbed OS

This is an example based on `mbed-os` cellular APIs that demonstrates a TCP or UDP echo transaction with a public echo server.

## Getting started

This particular cellular application uses a cellular network and network-socket APIs that are part of [`mbed-os`](https://github.com/ARMmbed/mbed-os).

The program uses a [cellular modem driver](https://github.com/mbed-ce/mbed-os/tree/master/connectivity/cellular/include/cellular/framework/API) using an external IP stack (LWIP) standard 3GPP AT 27.007 AT commands to setup the cellular modem and registers to the network.

After registration, the driver opens a point-to-point protocol (PPP) pipe using LWIP with the cellular modem and connects to internet. This driver currently supports UART data connection type only between your cellular modem and MCU.

For more information on Arm Mbed OS cellular APIs and porting guide, please visit the [Mbed OS cellular API](https://os.mbed.com/docs/latest/reference/cellular.html) and [contributing documentation](https://os.mbed.com/docs/mbed-os/latest/contributing/index.html).

> **ℹ️ Information**
>
> [Arm Mbed] is EOL'ing. The original document is adapted to
> [Mbed Community Edition](https://github.com/mbed-ce).

## Software requirements

Use cmake-based build system.
Check out [hello world example](https://github.com/mbed-ce/mbed-ce-hello-world) for getting started.

> **⚠️ Warning**
>
> Legacy development tools below are not supported anymore.
> - [Arm's Mbed Studio](https://os.mbed.com/docs/mbed-os/v6.15/build-tools/mbed-studio.html)
> - [Arm's Mbed CLI 2](https://os.mbed.com/docs/mbed-os/v6.15/build-tools/mbed-cli-2.html)
> - [Arm's Mbed CLI 1](https://os.mbed.com/docs/mbed-os/v6.15/tools/developing-mbed-cli.html)

For [VS Code development](https://github.com/mbed-ce/mbed-os/wiki/Project-Setup:-VS-Code)
or [OpenOCD as upload method](https://github.com/mbed-ce/mbed-os/wiki/Upload-Methods#openocd),
install below additionally:

-   [NuEclipse](https://github.com/OpenNuvoton/Nuvoton_Tools#numicro-software-development-tools): Nuvoton's fork of Eclipse
-   Nuvoton forked OpenOCD: Shipped with NuEclipse installation package above.
    Checking openocd version `openocd --version`, it should fix to `0.10.022`.

### Download the application

```sh
$ git clone https://github.com/mbed-nuvoton/NuMaker-mbed-ce-Cellular-example
$ cd NuMaker-mbed-ce-Cellular-example
$ git checkout -f master
```

### Change the network and SIM credentials

See the file `mbed_app.json` in the root directory of your application. This file contains all the user specific configurations your application needs. Provide the pin code for your SIM card, as well as any APN settings if needed. For example:

```json5
        "nsapi.default-cellular-plmn": 0,
        "nsapi.default-cellular-sim-pin": "\"1234\"",
        "nsapi.default-cellular-apn": 0,
        "nsapi.default-cellular-username": 0,
        "nsapi.default-cellular-password": 0
```

### Selecting socket type (TCP or UDP)


You can choose which socket type the application should use; however, please note that TCP is a more reliable transmission protocol. For example:


```json5

     "sock-type": "TCP",

```

### Turning modem AT echo trace on

If you like details and wish to know about all the AT interactions between the modem and your driver, turn on the modem AT echo trace.

```json5
        "cellular.debug-at": true
```

### Turning on the tracing and trace level

If you like to add more traces or follow the current ones you can turn traces on by changing `mbed-trace.enable` in mbed_app.json

```"target_overrides": {
        "*": {
            "mbed-trace.enable": true,
```

After you have defined `mbed-trace.enable: true`, you can set trace levels by changing value in `trace-level`

 ```"trace-level": {
            "help": "Options are TRACE_LEVEL_ERROR,TRACE_LEVEL_WARN,TRACE_LEVEL_INFO,TRACE_LEVEL_DEBUG",
            "macro_name": "MBED_TRACE_MAX_LEVEL",
            "value": "TRACE_LEVEL_INFO"
        }
```

### Board support

Mbed CE supports the in-tree [cellular modem drivers](https://github.com/mbed-ce/mbed-os/tree/master/connectivity/drivers/cellular).

In the following, we take **NuMaker-PFM-NUC472** board as an example for Mbed CE support.

## Compiling the application

Deploy necessary libraries
```
$ git submodule update --init
```
Or for fast install:
```
$ git submodule update --init --filter=blob:none
```

Compile with cmake/ninja
```
$ mkdir build; cd build
$ cmake .. -GNinja -DCMAKE_BUILD_TYPE=Develop -DMBED_TARGET=NUMAKER_PFM_NUC472
$ ninja
$ cd ..
```

## Running the application

Flash by drag-n-drop built image `NuMaker-mbed-ce-Cellular-example.bin` or `NuMaker-mbed-ce-Cellular-example.hex` onto **NuMaker-PFM-NUC472** board

Attach a serial console emulator of your choice (for example, PuTTY, Minicom or screen) to your USB device. Set the baudrate to 115200 bit/s, and reset your board by pressing the reset button.

You should see an output similar to this:

```
mbed-os-example-cellular
Establishing connection ......

Connection Established.
TCP: connected with echo.mbedcloudtesting.com server
TCP: Sent 4 Bytes to echo.mbedcloudtesting.com
Received from echo server 4 Bytes


Success. Exiting
```

## Troubleshooting

* Make sure the fields `sim-pin-code`, `apn`, `username` and `password` from the `mbed_app.json` file are filled in correctly. The correct values should appear in the user manual of the board if using eSIM or in the details of the SIM card if using normal SIM.
* Enable trace flag to have access to debug information `"mbed-trace.enable": true`.
* Try both `TCP` and `UDP` socket types.
* Try both `"lwip.ppp-enabled": true` and `"lwip.ppp-enabled": false`.
* The modem may support only a fixed baud-rate, such as `"platform.default-serial-baud-rate": 9600`.
* The modem and network may only support IPv6 in which case `"lwip.ipv6-enabled": true` shall be defined.
* The SIM and modem must have compatible cellular technology (3G, 4G, NB-IoT, ...) supported and cellular network available.

If you have problems to get started with debugging, you can review the [documentation](https://os.mbed.com/docs/latest/tutorials/debugging.html) for suggestions on what could be wrong and how to fix it.
