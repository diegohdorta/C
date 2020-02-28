---
layout: post
title: "Setting Up Yocto"
author: "Diego Dorta"
categories: yocto
tags: [artificial, intelligence, marchine, learning, code, AI, yocto, build]
---

The recommended and most appropriate way to guarantee determinism on development is to use *Yocto*. This post approaches the `fsl-arm-yocto-bsp`, for community go to [`fsl-community-bsp`](http://freescale.github.io/#download).

If you never set up on your machine the `prerequisites` for configuring and running *Yocto*, follow the next steps:

## **Software Requirements**

- Host OS: Tested on *Ubuntu 18.04 LTS*.
- Host packages:

You may need `root provigilies` to install the following essential packages:

```markdown
$ apt-get install gawk wget git-core diffstat unzip texinfo gcc-multilib build-essential chrpath socat libsdl1.2-dev
```
You will also need to install a few more packages required for `i.MX layers`:

```markdown
$ apt-get install libsdl1.2-dev xterm sed cvs subversion coreutils texi2html docbook-utils python-pysqlite2 help2man gcc g++ make desktop-file-utils libgl1-mesa-dev libglu1-mesa-dev mercurial autoconf automake groff curl lzop asciidoc u-boot-tools
```

## **Repo Utility**

You probably need to install `repo` utility once:

```markdown
$ mkdir ~/bin
$ curl https://storage.googleapis.com/git-repo-downloads/repo > ~/bin/repo
$ chmod a+x ~/bin/repo
$ PATH=${PATH}:~/bin
```
## Yocto Project Environment

```markdown
$ mkdir fsl-arm-yocto-bsp
$ cd fsl-arm-yocto-bsp
$ repo init -u https://source.codeaurora.org/external/imx/imx-manifest -b <branch> -m <manifest>
$ repo sync
```
Choose a branch:

- [imx-linux-morty](https://source.codeaurora.org/external/imx/imx-manifest/tree/?h=imx-linux-morty)
- [imx-linux-rocko](https://source.codeaurora.org/external/imx/imx-manifest/tree/?h=imx-linux-rocko)

Then, choose a manifest `imx-linux-morty`:

**i.MX8M Scale**:

- imx-4.9.51-8mq_beta.xml
- imx-4.9.51-8mq_ga-optee-demo.xml
- imx-4.9.51-8mq_ga.xml

**i.MX8QM**:

- imx-4.9.51-8qm_beta1-agl-demo.xml
- imx-4.9.51-8qm_beta1.xml
- imx-4.9.51-8qm_beta2.xml

**i.MX8QXP**:

- imx-4.9.51-8qxp_alpha.xml

For `imx-linux-rocko` manifests you can look [here](https://source.codeaurora.org/external/imx/imx-manifest/tree/?h=imx-linux-rocko).

## Examples

For `repo` tool, you can use as an example the following line for `i.MX8QM`:

```bash
$ repo init -u https://source.codeaurora.org/external/imx/imx-manifest -b local_imx-linux-morty -m imx-4.9.51-8qm_beta2.xml
$ repo sync
```
For building an image for `i.MX8QM` use the following line:

```bash
$ EULA=1 MACHINE=imx8qmmek DISTRO=fsl-imx-xwayland source ./fsl-setup-release.sh -b bld-xwayland
```
Then, inside `bld-xwayland` folder just run the `bitbake` command:

```bash
$ bitbake core-image-base
```
This command can take several hours, but it can guarantee you will have a full environment to create images and test them. 

## Flashing SD card

The output files can be found in `tmp/deply/image/<board_name>/`.

- Uncompressed the image using `bzunzip2` tool:

```bash
$ bunzip2 -f core-image-base-imx8qmmek.rootfs.sdcard.bz2
```

- Flash the uncompressed image into your SD card:

```bash
$ dd if=core-image-base-imx8qmmek.rootfs.sdcard of=/dev/sd<x> status=progress && sync
```


