# Copyright 2018 NXP

SUMMARY = "Library for quick CLI user prompts, input, and menus."
DESCRIPTION = "This project provides a Python 2.7/3.3+ library that allows the \
 user to quickly create CLI prompts for user input. The main features of Qprompt \
 are: Simple multi-entry menus; Prompt for typed (integer/float/string) input; \
 Optional default values and validity checks; Various CLI convenience functions; \
"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI[md5sum] = "2d348c56ea777903132208da9b98f869"
SRC_URI[sha256sum] = "fccdf75b66b79377e07a91bd40146a93e73bbfae8c399c3a12b7a78bfbdcd715"

HOMEPAGE = "https://pypi.org/project/qprompt/"

inherit pypi setuptools3

