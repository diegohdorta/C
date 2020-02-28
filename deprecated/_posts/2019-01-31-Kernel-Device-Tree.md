---
layout: post
title: "Kernel Device Tree Overview"
author: "Diego Dorta"
categories: kernel
tags: [ device, tree, overview, kernel, compile, arm, cross ]
---

The _device tree_ is a [_data-structure_](https://en.wikipedia.org/wiki/Data_structure) for describing hardware, which was originated
from [_Open Firmware_](https://en.wikipedia.org/wiki/Open_Firmware). The data structure can maintain many kind of data as internally 
it works based on a [_tree_](https://en.wikipedia.org/wiki/Tree_structure) of named nodes and properties. Nodes contain properties
and child nodes, while properties are [_name-value pairs_](https://en.wikipedia.org/wiki/Attribute%E2%80%93value_pair).

Assuming a correct _device tree_, the same compiled [_Linux Kernel_](https://www.kernel.org/) can support many
different hardware configurations within a wider architecture family. The _Kernel_
can read _device tree_ data from several architectures:

* [ARM](https://en.wikipedia.org/wiki/ARM_architecture);
* [x86](https://en.wikipedia.org/wiki/X86);
* [MicroBlaze](https://en.wikipedia.org/wiki/MicroBlaze);
* [Power Architecture](https://en.wikipedia.org/wiki/PowerPC);
* [SPARC](https://en.wikipedia.org/wiki/SPARC).

For ARM, the use of _device trees_ has turned mandatory for all new [_SoCs_](https://en.wikipedia.org/wiki/System_on_a_chip). This
can be seen as a remedy to the vast number of [_forks_](https://en.wikipedia.org/wiki/Fork_(system_call)) (_linux and U-Boot_) that has
historically been created to support different _ARM_ boards.

### Before DTB

* Kernel was dependent on the hardware description;
* Bootloader was loading kernel image, and then was executing it;
* Machine type is placed in _R1_;
* Bootloader was also setting up the ATAGS pointer in _R2_;
* _ATAGS_ is a list of tagged elements, each one starts with length and a tag (ATAG_CORE, ATAG_CMDLINE , ATAG_MEM, ATAG_NONE);

**NOTE:** *ATAGS = ARM tags, they are used to carry information such as memory size from boot code to kernel.*

* _ATAGS_ has to be in _RAM_;
* _R2_ should contain _ATAG_ address in recent _kernels_;
* _ATAGS_ must not extend beyond the **0x4000** boundary;
* _32_ bit aligned;
* Starts with _ATAG_CORE_, ends with _ATAG_NONE_;
* Must contain at least one _ATAG_MEM_;

Old style [_U-Boot_](https://www.denx.de/wiki/U-Boot) command was:

```bash
bootm <kernel addr>
```
### After DTB

* Hardware description is now in the DTB, which is a separate binary;
* The bootloader loads kernel and DTB as well;
* DTB can be found in arch/arm/boot/dts/<board>.dtb;
* No more machine type;
* R2 now contains DTB address;
* R2 now points to the DTB;
* R1 is not used anymore;
* The same kernel can be used for more than one board.

New style U-Boot command is:

```bash
bootm <kernel img addr> - <dtb addr>
```
Follow an example image describing the _device tree_ syntax:

<center><img src="{{site.url}}{{site.baseurl}}/assets/dt.png"/></center>

### Bindings

**NOTE:** _Examples removed from Freescale deprecated documents_.

Bindings is a description of how a device is described in the _device tree_.
Bindings for a lot of devices are well established and documented. You can
read about them in the existing _ePAPR_ and _IEEE 1275_ (_OpenFirmware_) documentation.
Bindings documentation can be found in _/Documentation/devicetree/bindings_. Read
more about a binding example [_here_](https://github.com/torvalds/linux/blob/master/Documentation/devicetree/bindings/pci/xilinx-nwl-pcie.txt).

Follow a few examples of _main nodes_ required properties:

1 - **Compatible**.

- "arm,cortex-a7-gic"
- "arm,cortex-a9-gic"

2 - **interrupt-controller**, which identifies the node as an interrupt controller.

3 - **interrupt-cells**, which specifies the number of cells needed to encode
an interrupt source. The type shall be a _u32_ and the value shall be _3_:

* 1st cell is the interrupt type; _0_ for _SPI interrupts_, _1_ for _PPI interrupts_.
* 2nd cell contains the interrupt number for the interrupt type. _SPI interrupts_ are in the range _[0-987]_. PPI interrupts are in the range _[0-15]_.
* 3rd cell is the flags, encoded as follows:

The _bits[3:0]_ trigger type and level flags:

* 1 = low-to-high edge triggered
* 2 = high-to-low edge triggered
* 4 = active high level-sensitive
* 8 = active low level-sensitive

The _bits[15:8]_, PPI interrupt cpu mask, each bit corresponds to each of the _8_ possible cpus
attached to the _GIC_. A bit set to '1' indicated the interrupt is wired to that
CPU. Only valid for PPI interrupts.

#### Bindings Examples

Freescale _Inter IC (I2C)_ and _High Speed Inter IC (HS-I2C)_ for `iMX`:

Required properties:
- compatible: should be "fsl,<chip>-i2c"
- reg: should contain I2C/HS-I2C registers location and length
- interrupts: should contain I2C/HS-I2C interrupt

Optional properties:
- clock-frequency: constains desired I2C/HS-I2C bus clock frequency in Hz.
The absence of the propoerty indicates the default frequency 100 kHz.

Examples:

```dtb
i2c@83fc4000 { /* I2C2 on i.MX51 */
	compatible = "fsl,imx51-i2c", "fsl,imx21-i2c";
	reg = <0x83fc4000 0x4000>;
	interrupts = <63>;
};
```

```dtb
i2c@70038000 { /* HS-I2C on i.MX51 */
	compatible = "fsl,imx51-i2c", "fsl,imx21-i2c";
	reg = <0x70038000 0x4000>;
	interrupts = <64>;
	clock-frequency = <400000>;
};
```
More details:

```dtb
i2c1: i2c@021a0000 {
	#address-cells = <1>;
	#size-cells = <0>;
	compatible = "fsl,imx6q-i2c", "fsl,imx21-i2c";
	reg = <0x021a0000 0x4000>;
	interrupts = <0 36 0x04>;
	clocks = <&clks 125>;
	status = "disabled";
};
```
```dtb
i2c2: i2c@021a4000 {
	#address-cells = <1>;
	#size-cells = <0>;
	compatible = "fsl,imx6q-i2c", "fsl,imx21-i2c";
	reg = <0x021a4000 0x4000>;
	interrupts = <0 37 0x04>;
	clocks = <&clks 126>;
	status = "disabled";
};
```
#### Adding Device Example

```dtb
mma8451@1c {
	compatible = "fsl,mma8451";
	reg = <0x1c>;
	position = <1>;
	vdd-supply = <&reg_sensor>;
	vddio-supply = <&reg_sensor>;
};
```
Bindings for `mma8450` which is a Freescale `MMA8450 3-Axis Accelerometer`:

```c
static const struct of_device_id mma8450_dt_ids[] = {
	{ .compatible = "fsl,mma8450", },
	{ /* sentinel */ }
};
```

Required properties:

- compatible : "fsl,mma8450".
- reg: the I2C address of MMA8450

Example:

```dtb
accelerometer: mma8450@1c {
	compatible = "fsl,mma8450";
	reg = <0x1c>;
};
```
#### GPIO Example

Suppose the following constants:

```c
#define KEY_VOLUMEDOWN 114
#define KEY_VOLUMEUP 115
#define KEY_POWER 116
```
In _device tree_ format:

```dtb
gpio-keys {
	compatible = "gpio-keys";
	
	power {
		label = "Power Button";
		gpios = <&gpio3 29 1>;
		linux,code = <116>; /* KEY_POWER */
		gpio-key,wakeup;
	};
	
	volume-up {
		label = "Volume Up";
		gpios = <&gpio1 4 1>;
		linux,code = <115>; /* KEY_VOLUMEUP */
	};
	
	volume-down {
		label = "Volume Down";
		gpios = <&gpio1 5 1>;
		linux,code = <114>; /* KEY_VOLUMEDOWN */
	};
};
```

For more examples, see this [document](https://community.nxp.com/docs/DOC-104818).

### Compiling

The _DTS_ file is located in: _arch/arm/boot/dts_. The files with the _.dtsi_ name
are analogous to the _.h_ (_headers_) files for the _DTS_.
The compiler for this is called _DTC_ and can be found in: _scripts/dtc/dtc_.
Download the _Kernel_ using _git_ tool:

```bash
$ git clone https://github.com/torvalds/linux.git
```
To compile it is simple, just run the following lines:

```bash
$ export ARM=<your_arch>
$ export CROSS_COMPILE=<your_cross_compiler>
$ make <your_board>_defconfig
$ make
```
The _DTB_ is generated by _DTC_ and it can be rebuild like this:

```bash
$ make <board_name>.dtb
```
