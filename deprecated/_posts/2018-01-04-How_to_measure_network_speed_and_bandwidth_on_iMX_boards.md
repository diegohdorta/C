---
layout: post
title: "Network and Bandwidth on i.MX Boards"
author: "Diego Dorta"
categories: artificial
tags: [ iperf, TCP, network, performance, bandwidth ]
---

This post is designated for those who want to test the network performance in terms of speed and bandwidth on `iMX` boards.
The [`iperf`](https://iperf.fr/) tool is used for executing this test, it is very reliable and also an open source tool released under a three-clause `BSD license`.

The `iperf` works by the client side sending data to the server side, making it possible to measure the network throughput between them.
The throughput is the transfer rate of data from one place to another in a period of time, it is also measured in `Kbps`, `Mbps`, and `Gbps`.

The diagram shows the communication between machines:

<center><img src="{{site.url}}{{site.baseurl}}/assets/iperf_connection.jpg" width="80%"/></center>

## Iperf on Host Machine

For installing the iperf tool on your host machine, use the `apt-get` repository:

```console
$ apt-get install iperf
```

## Iperf tool binaries

This section describes how to add the iperf package to fsl-community-bsp. For this example it was used a `iMX6QSabre SD` Board:

### Yocto Project

To install the FSL Community BSP, follow the steps describes [here](http://freescale.github.io/#download).

For including `iperf` tool, add the following line inside `local.conf`:

```console
CORE_IMAGE_EXTRA_INSTALL += " iperf3 "
```

Then, run the _bitbake_ command:

```console
$ bitbake core-image-base
```
Your image is prepared for running iperf tool.

## Iperf test

Follow an example showing iperf where iMX board is a server, and the computer
is a client for sending data to the server. With this test it will be possible
to measure the iMX network performance:

For running iMX as a server:

```console
# iperf -s
------------------------------------------------------------
Server listening on TCP port 5001
TCP window size: 85.3 KByte (default)
------------------------------------------------------------
```
* -s argument is used for specifying server

The above command, starts iperf server on the iMX board, and it by default runs on the port 5001,
it also reports that the default TCP Windows Size is `85.3KByte` (These configurations can be changed using the corresponding parameters).

If your board does not get an ip, run the follow command: **udhcp**

For running the computer as a client:

```console
 $ iperf -c <imx_board_ip>
```
* -c argument is used for specifying client

## Iperf results

Running the above command, the connection will start transfer the data and show the results:

```console
 $ iperf -c 10.29.244.45
 ------------------------------------------------------------
 Client connecting to 10.29.244.45, TCP port 5001
 TCP window size: 85.0 KByte (default)
 ------------------------------------------------------------
 [  3] local 10.29.240.152 port 60642 connected with 10.29.244.45 port 5001
 [ ID] Interval       Transfer     Bandwidth
 [  3]  0.0-10.0 sec   522 MBytes   438 Mbits/sec
```

From the above output, you can see that the iMX board got a speed of **438Mbits/sec**.

The output shows something more:

* **Interval**:
Interval specifies the time duration for which the data is transferred.

* **Transfer**:
All data transferred using iperf is through memory, and is flushed out after completing the test.
So there is no need to clear the transferred file after the test. This column shows the transferred data size.

* **Bandwidth**:
This shows the rate of speed with which the data is transferred.

On the iMX server side, you also have the results:
```
 # iperf -s
 ------------------------------------------------------------
 Server listening on TCP port 5001
 TCP window size: 85.3 KByte (default)
 ------------------------------------------------------------
 [  4] local 10.29.244.45 port 5001 connected with 10.29.240.152 port 60642
 [ ID] Interval       Transfer     Bandwidth
 [  4]  0.0-10.0 sec   522 MBytes   437 Mbits/sec
```

These results show the network throughput of the iMX6Sabre SD board.
It is also possible to change the sides, by making the computer be a server and the iMX board a client.
