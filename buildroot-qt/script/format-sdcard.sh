#!/bin/bash

echo
echo "Please make sure you have a SD card connected!"
echo
read -p "Press [Enter] to continue..."

(
echo "p"
echo "1"
echo "4000"
echo "50000"
echo "n"
echo "p"
echo "2"
echo "50001"
echo "150000"
echo "w"
) | fdisk /dev/sdb

mkfs.vfat -F 16 -n boot /dev/sdb1
mkfs.ext4 /dev/sdb2 -L rootfs

echo
echo "Your SD card is partitioned"
echo
