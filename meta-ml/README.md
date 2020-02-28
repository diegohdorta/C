meta-ml
=======



Inside your source folder, clone the repository:


$ git clone https://github.com/diegohdorta/meta-ml.git

Then, include in your BB layer the meta-ml layer:


BBLAYERS += "${BSPDIR}/sources/meta-ml"

Inside the `local.conf` put the packages names:


CORE_IMAGE_EXTRA_INSTALL += "<packages>"

