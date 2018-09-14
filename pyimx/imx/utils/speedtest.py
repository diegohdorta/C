"""**Speed Test Module**

Speed test module to measure ethernet performance on i.MX Boards.

:platform: Unix
:synopsis: This module contains functions to measure ethernet performance: ping, download and upload rate.

.. moduleauthor:: Diego Henrique Dorta <diego.dorta@nxp.com>
   .. note:: 04/17/2018 [diego.dorta]  first version released

"""
import pyspeedtest as speed

def speedtest():
    """
    Returns the performance of ethernet in 'ms' and 'Mbps'.
    """
    print('Ping rate: ' + str(ping_rate()) + ' ms')
    print('Download speed: ' + str(download_rate()) + ' Mbps')
    print('Upload speed: ' + str(upload_rate()) + ' Mpbs')

def ping_rate():
    """
    Returns ping rate.
    """
    st = speed.SpeedTest()
    return st.ping()

def download_rate():
    """
    Returns download rate.
    """
    st = speed.SpeedTest()
    return st.download()

def upload_rate():
    """
    Returns upload rate.
    """
    st = speed.SpeedTest()
    return st.upload()

