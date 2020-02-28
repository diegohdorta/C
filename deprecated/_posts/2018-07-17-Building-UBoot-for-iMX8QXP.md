---
layout: post
title: "Building U-Boot for iMX8 QXP Board"
author: "Diego Dorta"
categories: tutorial
tags: [ imx8, qxp, automotive, uboot, source, code, unix ]
---

The purpose behind this post consists in explaining a way to get started with `iMX8QXP MEK` board from its source code. Due the constant maintenance this post may stop working eventually.

# Cross-compiler tool

Either go to this [`link`](http://shlinux12.ap.freescale.net/Yocto_SDK/4.9.51-mx8-beta2/) to download the `toolchain`, or use the following line:

```bash
$ wget http://shlinux12.ap.freescale.net/Yocto_SDK/4.9.51-mx8-beta2/fsl-imx-internal-xwayland-glibc-x86_64-fsl-image-gui-aarch64-toolchain-4.9.51-mx8-beta.sh
```
Then, change the file to executable mode:

```bash
$ chmod +x fsl-imx-internal-xwayland-glibc-x86_64-fsl-image-gui-aarch64-toolchain-4.9.51-mx8-beta.sh
```
Run the script to install the `toolchain`:

```bash
$ ./fsl-imx-internal-xwayland-glibc-x86_64-fsl-image-gui-aarch64-toolchain-4.9.51-mx8-beta.sh
```
To invoke the `toolchain` use the following line:

```bash
$ source <path_to_toolchain>/environment-setup-aarch64-poky-linux
```
Create a folder to your environment:

```bash
$ mkdir build 
$ cd build/
```
# Extra tool

The `mkimage` tool is useful to gather all the `binaries`. Download it as follow:

```bash
$ git clone https://bitbucket.sw.nxp.com/scm/imx/imx-mkimage.git
$ cd imx-mkimage/
$ git checkout origin/imx_4.9.88_imx8qxp_beta2
```
Build `mkimage` tool to prepare the files:

```bash
$ make SOC=iMX8QX
```
# U-Boot Step

Download `U-Boot` as follow:

```bash
$ git clone https://bitbucket.sw.nxp.com/scm/imx/uboot-imx.git
$ git checkout origin/imx_v2017.03_4.9.88_imx8qxp_beta2
```
Then, compile the `U-Boot`:

```bash
$ make imx8qxp_mek_defconfig
$ make
```
Copy the `u-boot.bin` binary file to:

```bash
$ cp u-boot.bin ../imx-mkimage/iMX8QX/
```
## ATF - Arm Trusted Firmware

Download `ATF` as follow:

```bash
$ git clone https://bitbucket.sw.nxp.com/scm/imx/arm-trusted-firmware.git
$ cd arm-trusted-firmware/
$ git checkout imx_1.4.y
```
Export the `toolchain`:

```bash
$ source <path_to_toolchain>/environment-setup-aarch64-poky-linux
$ unset LDFLAGS
```
Then, compile:

```bash
$ make PLAT=imx8qxp bl31
$ cp build/imx8qxp/release/bl31.bin ../imx-mkimage/iMX8QX/
```
Copy the binary to:

```bash
$ cd build/imx-mkimage/iMX8QX
$ cp bl31.bin u-boot-atf.bin
```
The `ATF` must be concatenated (and padded) with `U-Boot` as follow:

```bash
$ ../mkimage_imx8 -commit > head.hash
$ cat u-boot.bin head.hash > u-boot-hash.bin
$ dd if=u-boot-hash.bin of=u-boot-atf.bin bs=1K seek=128 && sync
```
## iMX SC Firmare

For this step, install the following package:

```bash
$ apt-get install srecord
```
Download the `firmware`:

```bash
$ cd build/
$ git clone https://bitbucket.sw.nxp.com/scm/imx/imx-sc-firmware.git
```
Compile the required tools:

```bash
$ cd imx-sc-firmware/tools/
$ ./tool_setup
$ rm -fr srec
```
Compile the `firmware`:

```bash
$ cd ../firmware/
$ export TOOLS=../tools
$ make qx R=B0 B=mek M=1
```
## iMX Linux Firmware

```bash
$ git clone https://bitbucket.sw.nxp.com/scm/imx/linux-firmware-imx.git
```
## Final Step

Below are different ways to use `mkimage` tool, choose one:

```bash
$ ./imx-mkimage/mkimage_imx8 \
-soc QX \
-rev B0 \
-append linux-firmware-imx/firmware/seco/ahab-container.img \
-c -scfw imx-sc-firmware/firmware/build_mx8qx/scfw_tcm.bin \ 
-ap imx-mkimage/iMX8QX/u-boot-atf.bin a35 0x80000000 \
-out ./flash.bin
```
Or:

```bash
$ cd imx-mkimage/
$ cp ../linux-firmware-imx/firmware/seco/ahab-container.img iMX8QX/
$ cp ../imx-sc-firmware/firmware/build_mx8qx/scfw_tcm.bin iMX8QX/
$ make SOC=iMX8QX flash
```
## Flashing

```bash
$ dd if=flash.bin of=/dev/<x> bs=1K seek=32 status=progress && sync
```




