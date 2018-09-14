#!/bin/bash

echo "# This script compiles Buildroot with QT5 #"
echo

read -p "Press [Enter] to continue..."

echo "Downloading Buildroot..."
wget https://buildroot.org/downloads/buildroot-2016.11.tar.gz
tar xvf buildroot-2016.11.tar.gz

rm -rf xvf buildroot-2016.11.tar.gz

mv buildroot-2016.11 build

cp configs/config-freescale-qt5_defconfig build/configs

cd build

# Temporary

mkdir board/freescale/imx7dsdb/patches
mkdir board/freescale/imx7dsdb/patches/linux

cp ../patches/* board/freescale/imx7dsdb/patches/linux

# ---------

echo
echo "Configuring..."
echo
make config-freescale-qt5_defconfig

echo
echo "Starting build, this may take a while..."
make

echo "Use code inside script folder to flash the SD card."
echo "The examples are inside /usr/lib/examples"
echo "For testing: ./analogclock -qws -platform linuxfb"
