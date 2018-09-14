Contribute
==========

If you interest on helping with PyIMX project, you can start by downloading the github repo::

   $ git clone https://github.com/diegohdorta/pyimx.git
   $ cd pyimx/
   
Then, you can use a *script* to help creating the required files::

   $ sh script/new_module.sh
   
Enter the following requirements::

   Module name: test
   Developer: John
   
Your *python file* will be created on *imx/developing* folder. To import it use the following line::

	$ python3
	Python 3.6.5 (default, Apr  1 2018, 05:46:30) 
	[GCC 7.3.0] on linux
	Type "help", "copyright", "credits" or "license" for more information.
	>>>
	>>> from imx.developing import test
	>>> test.who()
	>>> Written by: John

Now you can read your module. Generate a patch with your modifications and send to PyIMX team::

    $ git add imx/developing/test.py
    $ git commit -s -m "NM: Test for ..."
    $ git format-patch -1
    $ git send-email --to diego.dorta@nxp.com test.patch

We will review your module, in case something went wrong you will be notified, if not it will be release on our next release.

