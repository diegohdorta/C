LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI[md5sum] = "7d7cbe4c750f992d1fe1bd847d87eace"
SRC_URI[sha256sum] = "2767ae04a47d3d9f9d210be70f15f866381f9bb464dd21ce9abd422fa2ec3b5f"

SRC_URI = "https://github.com/diegohdorta/imx-ml-demos/archive/master.zip"

S = "${WORKDIR}/imx-ml-demos-master"

do_install() {
    install -d -m 755 ${D}/opt/demos
    cp -rfv ${S}/* ${D}/opt/demos
}

FILES_${PN} += "/opt/demos"
