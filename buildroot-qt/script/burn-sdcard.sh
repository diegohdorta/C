#!/bin/bash

mkdir /media/diego/boot
mkdir /media/diego/rootfs

mount /dev/sdb1 /media/diego/boot
mount /dev/sdb2 /media/diego/rootfs

echo "Partitions mounted on: /media/${USER}/"

dd if=output/images/u-boot.imx of=/dev/sdb bs=1K seek=1 ; sync
cp output/images/zImage /media/diego/boot
cp output/images/imx7d-sdb.dtb /media/diego/boot
tar -xvf output/images/rootfs.tar -C /media/diego/rootfs




