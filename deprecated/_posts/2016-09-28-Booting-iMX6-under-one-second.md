---
layout: post
title: "Booting i.MX6Q SDB under one second"
author: "Diego Dorta"
categories: tutorial
tags: [ fast-boot, uboot, falconmode, IMX6Q ]
---

I'm running the NXP **i.MX6Q SDB** using U-Boot Falcon mode to reduce booting time. I currently managed to boot a complete Linux image up to the login prompt in about `0.9 second`.

The links are available below:

* Video on [Youtube](https://www.youtube.com/watch?v=Zl-Ypk9S-dc).

<iframe width="560" height="315" src="https://www.youtube.com/embed/Zl-Ypk9S-dc" frameborder="0" allowfullscreen align="center"></iframe>

* Pre-built image on [Dropbox](https://www.dropbox.com/s/d6vgztz701blbmc/falconmode_imx6sabresd.sdcard?dl=0).

The statistical analysis:

<img src="{{site.url}}{{site.baseurl}}/assets/graph.jpg">

To upload the image into the SD card, use the following command, and you may need `root privileges`:

```console
$ dd if=falconmode_imx6qsabresd.sdcard of=/dev/sd<x> status=progress && sync
```
