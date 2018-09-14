"""**Sample Module**

Python sample to start developing on i.MX Boards.

:platform: Unix
:synopsis: This module contains functions to return basic features.

.. moduleauthor:: Diego Henrique Dorta <diego.dorta@nxp.com>
   .. note:: 04/17/2018 [diego.dorta]  first version released

"""
import sys
import platform as p

def code_version():
    """
    Returns code version.
    """
    v = 'v0.0.1b'
    return v

def system():
    """
    Returns the operating system name.
    """
    return p.system()

def release():
    """
    Returns the operating system release number
    """
    return p.release()

def version():
    """
    Returns the more detailed system version
    """
    return p.machine()

def machine():
    """
    Returns a hardware-type identifier such as 'i386'
    """
    return p.machine()

def who():
    """
    Returns developer name.
    """
    who = 'Diego Dorta'
    print("Written by: %s" % str(who))

class Sample:
    def __init__(self, name, color):
        """
        **Constructor**
        Parameters
        ----------
        name : `string`
            Any name.
        color : `string`
            Any color.
        """
    
        self.color = color
        self.name = name

    def show(self):
        """
        Print class examples
        """
        print("The example color is: " + self.color + ".")
        print(self.name + " is your the example's name.")
