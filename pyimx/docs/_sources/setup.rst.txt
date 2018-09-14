=================
Environment Setup
=================

To use PyIMX on your image you must have installed a few prerequisites. Here are the list and a basic guide to help you to setup your build machine:

- `Python3.x <https://www.python.org/download/releases/3.0/>`_ or higher.
- `Pip3 <https://pypi.org/project/pip/>`_ package manager.
- `Pyspeedtest <https://pypi.org/project/pyspeedtest/>`_

Yocto Source Code
-----------------

To download the platform source `code <http://freescale.github.io/#download>`_. Start by the following steps:

You need to have repo utility installed::

    $ mkdir ~/bin
    $ curl http://commondatastorage.googleapis.com/git-repo-downloads/repo > ~/bin/repo
    $ chmod a+x ~/bin/repo

Download the source code::

    $ PATH=${PATH}:~/bin
    $ mkdir fsl-community-bsp
    $ cd fsl-community-bsp
    $ repo init -u https://github.com/Freescale/fsl-community-bsp-platform -b rocko
    $ repo sync

For including *Python* and *pip* tool, add the following line inside *local.conf*::

    CORE_IMAGE_EXTRA_INSTALL += " python3 pip3 "

Then, run the bitbake command::

    $ bitbake core-image-base


