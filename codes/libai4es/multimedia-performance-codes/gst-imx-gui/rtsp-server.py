#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Copyright (C) 2019 Diego Dorta
Diego Dorta <diego.dorta@nxp.com>
"""
import socket
import sys
import gi
gi.require_version('Gst', '1.0')
from gi.repository import Gst


def establishRtspConnection():
    mcastIP = '225.0.0.1'
    mcastPort = 10000
    message = b'I am alive, watch me!'
    fd = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    fd.sendto(message, (mcastIP, mcastPort))


 
if __name__ == '__main__':
    establishRtspConnection()
    
        
    
    
    
    
    
  #  gst-variable-rtsp-server -p 9001 -u "v4l2src device=/dev/video0 ! video/x-raw,width=640,height=480 ! v4l2h264enc ! rtph264pay name=pay0 pt=96"
