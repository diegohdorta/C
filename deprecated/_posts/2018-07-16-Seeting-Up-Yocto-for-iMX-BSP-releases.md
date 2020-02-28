---
layout: post
title: "Setting up Yocto for i.MX BSP releases"
author: "Diego Dorta"
categories: yocto
tags: [ yocto, release, bsp, qxp, imx8, imx8qxp, image, imx ]
---

This previous [`post`](https://diegodorta.com.br/yocto/Setting-Up-Yocto.html) may not work all time due the constant maintenance.
To solve this issue, this post intents to teach how to start using actual `i.MX BSP releases` from [`code aurora`](https://source.codeaurora.org/external/imx/imx-manifest).

The newest release for `iMX8QXP` is `imx-4.9.88-2.2.0-8qxp_beta2` over the branch [`imx-linux-rocko`](https://source.codeaurora.org/external/imx/imx-manifest/tree/README?h=imx-linux-rocko).
The following instructions can be applied to any `new branch and release`. 

See this [`post`](https://diegodorta.com.br/yocto/Setting-Up-Yocto.html) for `prerequisites`.

## Yocto Project Environment

```bash
$ mkdir <release>
$ cd <release>
$ repo init -u https://source.codeaurora.org/external/imx/imx-manifest -b <branch name> [ -m <release manifest>]
$ repo sync
```
## Examples

For `repo` tool, you can use as an example the following line for `i.MX8QXP`:

```bash
$ repo init -u https://source.codeaurora.org/external/imx/imx-manifest  -b imx-linux-rocko -m imx-4.9.88-2.2.0-8qxp_beta2.xml
$ repo sync
```
This example approaches builds `4.9.88-2.2.0 i.MX 8QXP Beta2` release:

```bash
$ EULA=1 MACHINE=imx8qxpmek DISTRO=fsl-imx-xwayland source ./fsl-setup-release.sh -b bld-xwayland
```
Then, inside `bld-xwayland` folder run `bitbake`:

```bash
$ bitbake core-image-base
```
## Flashing SD Card

The output files can be found in `tmp/deply/image/<board_name>/`.

- Uncompressed the image using `bzunzip2` tool:

```bash
$ bunzip2 -f core-image-base-imx8qxpmek.rootfs.sdcard.bz2
```

- Flash the uncompressed image to SD card:

```bash
$ dd if=core-image-base-imx8qxpmek.rootfs.sdcard of=/dev/sd<x> status=progress && sync
```


