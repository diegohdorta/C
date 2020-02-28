# Copyright 2019 NXP

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI[md5sum] = "ad09aa090e4e9f209e6ff455bfa3d11c"
SRC_URI[sha256sum] = "d1f167054cec10987094861468df9c2c63b07cd97693809bd22e634d62215b26"


DEPENDS = "cmake-native"
RDEPENDS_${PN} = "sqlite3"

SRC_URI = "https://files.pythonhosted.org/packages/35/8d/e4ddf60452e2fb1ce3164f774e68968b3f110f1cb4cd353235d56875799e/dlib-19.16.0.tar.gz"



S = "${WORKDIR}/dlib-19.16.0"



inherit setuptools3







# inherit pkgconfig cmake pkgconfig pypi setuptools3
#RDEPENDS_${PN} += "python3-core python3-setuptools python3-numpy"
#PYPI_PACKAGE = "dlib"
