# Copyright 2018 NXP

SUMMARY = "Scientific Library for Python"
SECTION = "devel/python"
HOMEPAGE = "https://pypi.python.org/pypi/scipy"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

PYPI_PACKAGE="scipy"

SRC_URI[md5sum] = "aa6bcc85276b6f25e17bcfc4dede8718"
SRC_URI[sha256sum] = "878352408424dffaa695ffedf2f9f92844e116686923ed9aa8626fc30d32cfd1"

inherit pypi setuptools distutils

RDEPENDS_${PN} += "python-core python-numpy python-distutils"
DEPENDS = "python-numpy-native openblas"
