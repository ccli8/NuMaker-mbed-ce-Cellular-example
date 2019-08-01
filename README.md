This example is modified from mbed-os-example-cellular.

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

2. If run SIM7020, please use Mbed-OS 5.13.1 and later.

3. Add the cellular device support in mbed_app.json as below.

   For SIMCOM SIM7020, please add the first two configurations. The drivers.uart-serial-rxbuf-size should be MAX_PACKET_SIZE*2+100.
    "target_overrides": {
        "*": {
            "target.extra_labels_add": ["SIM7020"],
            "drivers.uart-serial-rxbuf-size": 4196,
            "target.network-default-interface-type": "CELLULAR",

   For QUECTEL BG96, please add the first three configurations.
    "target_overrides": {
        "*": {
            "QUECTEL_BG96.provide-default": true,
            "QUECTEL_BG96.tx": "D1",
            "QUECTEL_BG96.rx": "D0",
            "target.network-default-interface-type": "CELLULAR",

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

(Note: To see this example in a rendered form you can import into the Arm Mbed Online Compiler, please see [the documentation](https://os.mbed.com/docs/mbed-os/latest/apis/cellular-api.html#cellular-example-connection-establishment).)

## Getting started

This particular cellular application uses a cellular network and network-socket APIs that are part of [`mbed-os`](https://github.com/ARMmbed/mbed-os).

The program uses a [cellular modem driver](https://github.com/ARMmbed/mbed-os/tree/master/features/cellular/framework/API) using an external IP stack (LWIP) standard 3GPP AT 27.007 AT commands to setup the cellular modem and registers to the network.

After registration, the driver opens a point-to-point protocol (PPP) pipe using LWIP with the cellular modem and connects to internet. This driver currently supports UART data connection type only between your cellular modem and MCU.

For more information on Arm Mbed OS cellular APIs and porting guide, please visit the [Mbed OS cellular API](https://os.mbed.com/docs/latest/reference/cellular.html) and [contributing documentation](https://os.mbed.com/docs/mbed-os/latest/contributing/index.html).

### Download the application

```sh
$ mbed import mbed-os-example-cellular
$ cd mbed-os-example-cellular

#OR

$ git clone git@github.com:ARMmbed/mbed-os-example-cellular.git
$ cd mbed-os-example-cellular
```

### Change the network and SIM credentials

See the file `mbed_app.json` in the root directory of your application. This file contains all the user specific configurations your application needs. Provide the pin code for your SIM card, as well as any APN settings if needed. For example:

```json
        "nsapi.default-cellular-plmn": 0,
        "nsapi.default-cellular-sim-pin": "\"1234\"",
        "nsapi.default-cellular-apn": 0,
        "nsapi.default-cellular-username": 0,
        "nsapi.default-cellular-password": 0
```

### Selecting socket type (TCP or UDP)


You can choose which socket type the application should use; however, please note that TCP is a more reliable transmission protocol. For example:


```json

     "sock-type": "TCP",

```

### Turning modem AT echo trace on

If you like details and wish to know about all the AT interactions between the modem and your driver, turn on the modem AT echo trace.

```json
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

The [cellular modem driver](https://github.com/ARMmbed/mbed-os/tree/master/features/cellular/framework/API) in this example uses PPP with an Mbed-supported external IP stack. It supports targets when modem exists on the Mbed Enabled target as opposed to plug-in modules (shields). For more details, please see our [Mbed OS cellular documentation](https://os.mbed.com/docs/mbed-os/latest/apis/cellular-api.html).

Currently supported boards with onboard modem chips are:

[u-blox C027](https://os.mbed.com/platforms/u-blox-C027/)
[MultiTech MTS Dragonfly](https://os.mbed.com/platforms/MTS-Dragonfly/)


## Compiling the application

The master branch is for daily development and it uses the latest mbed-os/master release.

To use older versions update Mbed OS release tag, for example:

```
mbed releases
 * mbed-os-5.10.4
   ...
mbed update mbed-os-5.10.4
```

You may need to use `--clean` option to discard your local changes (use with caution).

Use Mbed CLI commands to generate a binary for the application. For example, in the case of GCC, use the following command:

```sh
$ mbed compile -m YOUR_TARGET_WITH_MODEM -t GCC_ARM
```

## Running the application

Drag and drop the application binary from `BUILD/YOUR_TARGET_WITH_MODEM/GCC_ARM/mbed-os-example-cellular.bin` to your Mbed Enabled target hardware, which appears as a USB device on your host machine.

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
