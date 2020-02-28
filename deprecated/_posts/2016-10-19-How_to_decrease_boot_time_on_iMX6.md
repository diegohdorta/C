---
layout: post
title: "Decreasing Boot Time on i.MX6"
author: "Diego Dorta"
categories: tutorial
tags: [ fast-boot, uboot, falconmode, IMX6QDL ]
---

This tutorial shows how to decrease boot time on a `i.MX6 Sabre SD` using `Falcon mode`. The Kernel used is the `4.8 linux stable version`.

Falcon mode skips U-Boot completely and leverages SPL to boot the Kernel and load the rootfs faster.
It still adds U-Boot to the image as it's used during configuration and loading the Kernel and dtb,
but after this configuration is done it can skip U-Boot completely jumping directly to the Kernel.

If you want to know more about Falcon mode, please check [here](http://git.denx.de/?p=u-boot.git;a=blob;f=doc/README.falcon;h=e9f8a7583c721cd96eb364ff23d591c0284c70b3;hb=HEAD).

## U-Boot

U-Boot 2016.11 already enables Falcon mode for `i.MX6` sabresd board.

The patch is available [here](http://git.denx.de/?p=u-boot/u-boot-imx.git;a=commitdiff;h=d96796ca23b2ebcb7ce58c250e5a44152a652a45;hp=940afa4e544bdc2365d85bca78e0dcb847002eab).

To build an U-Boot image follow the next steps:

Download U-Boot:
```console
 $ git clone git://git.denx.de/u-boot.git
```

Change to the most recent branch:
```console
 $ git checkout -b 2016.11 v2016.11
```

Configure U-Boot to using the following command:

```console
 $ make mx6sabresd_spl_defconfig
```

Compile it:
```console
 $ make
```
## Kernel

Download the patch [here](https://www.dropbox.com/s/73kpx1lilgyuemw/0001-Minimal-Kernel-Features-for-i.MX6Q.patch?dl=0) or the config file [here](https://www.dropbox.com/s/obdl6glnaef6jyr/minimal_imx6q_defconfig?dl=0).

I'm reducing the kernel configuration in order to get a smaller kernel, which reduces
the booting time.

To do that, follow the next steps:

Download the Kernel:

```console
 $ git clone git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git
```

Change to the most recent branch:
```console
$ git checkout origin/linux-4.8.y -b local_linux-4.8
```

Apply the patch:
```console
  $ git am 0001-Minimal-Kernel-Features-for-i.MX6Q.patch
```

```console
  $ make minimal_imx6q_defconfig
```

Compile it generating uImage:
```console
  $ make uImage LOADADDR=0x10800000
```

## Root File System

Download the `local.conf` [here](https://www.dropbox.com/s/rdx6p2h3c4tdd6g/local.conf?dl=0).

```console
 $ bitbake core-image-base
```

After that, extract using `cpio` command:

```console
 $ mkdir rootfs
 $ cd rootfs/
 $ cpio -id < core-image-minimal-mx6sabresd.rootfs.cpio
```

## Preparing SD card

Create a partition using a tool such as GParted. The raw space must have at least `5MB` and the rootfs partition `15MB`.

<img src="{{site.url}}{{site.baseurl}}/assets/gparted.png">

## Copying U-Boot

The `SPL` file and `u-boot.img` are flashed into the raw space:

```console
 $ DEV=/dev/sd<x>
```
You may need `root privileges`:

```console
 $ dd if=SPL of=$DEV bs=1K seek=1 status=progress && sync
 $ dd if=u-boot.img of=$DEV bs=1K seek=69 status=progress && sync
```

## Copying the File System

Copy the file system into the root partition:

```console
 $ sudo cp -aR rootfs/* /media/root
```

## Copying Kernel and DTB

Power up the board and go into U-Boot. Upload Kernel and dtb to the board using TFTP with the following steps:

Set up your host IP:

```console
 # setenv serverip 192.168.1.10
```

Download the dtb file:
```console
 # dhcp ${fdt_addr} imx6q-sabresd.dtb
```

Download the Kernel image:
```console
 # dhcp ${loadaddr} uImage
```

Writing the Kernel at 2MB offset:
```console
 # mmc write ${loadaddr} 0x1000 0x4000
```

Setup the Kernel bootargs:
```console
 # setenv bootargs 'console=ttymxc0,115200 root=/dev/mmcblk1p1 rootfstype=ext4 rootwait quiet rw'
```

Prepare args:
```console
 # spl export fdt ${loadaddr} - ${fdt_addr}
```

Writing args 1MB data (0x800 sectors) to 1MB offset (0x800 sectors):
```console
 # mmc write 18000000 0x800 0x800
```

Boot the board with KEY_VOL_UP pressed and the SPL binary are launched the kernel directly.

## Images

Download the SD card image [here](https://www.dropbox.com/s/d6vgztz701blbmc/falconmode_imx6sabresd.sdcard?dl=0).

The image is available for download. To copy this image into the SD card, use the following command, and you may need `root privileges`:

```console
 $ dd if=falconmode_imx6sabresd.sdcard of=/dev/sd<x> status=progress && sync
```

