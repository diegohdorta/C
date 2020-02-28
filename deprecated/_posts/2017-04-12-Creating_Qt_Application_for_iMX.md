---
layout: post
title: "Creating Qt Application for i.MX"
author: "Diego Dorta"
categories: tutorial
tags: [ IMX7D, Qt5, buildroot, embedded, demo, sht11, sensor ]
---

The following tutorials provide sample guides to develop Qt Applications for running on `i.MX` platform.

Initially, the link below summarizes how to build an environment to support `Qt` development tool on `embedded systems`:

[Embedded Qt with Buildroot](https://github.com/diegohdorta/feynman/tree/master/buildroot-qt).

The following link demonstrates how to configure an Integrated Development Environment (IDE) `Qt Creator`:

[Setting up Qt Creator for development](https://github.com/diegohdorta/feynman/blob/master/buildroot-qt/docs/qtcreator.md).

The created environment correlates low and high level programming languages by using Kernel driver and a `Qt` application.

The NXP i.MX7D SabreSD Board has a MikroBus connector for click boards, the main idea for this demo is to display the temperature measured by the `SHT11` sensor.

[Temperature demo](https://github.com/diegohdorta/feynman/tree/master/buildroot-qt/examples/demo_imx7).

The video demonstration is available on YouTube :

[iMX7D: Running a Qt Application that displays the temperature](https://www.youtube.com/watch?v=O5F1N312Bhg).

<iframe width="560" height="315" src="https://www.youtube.com/embed/O5F1N312Bhg" frameborder="0" allowfullscreen align="center"></iframe>

**Notes:**

* For touchscreen support, read [Calibration](https://github.com/diegohdorta/feynman/blob/master/buildroot-qt/examples/calibration.md).
* To add drivers support on Kernel, read the [Device Tree Support](https://imxdev.gitlab.io/tutorial/How_to_add_DT_support_for_a_driver/).
