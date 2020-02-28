#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Copyright (C) 2019 Diego Dorta
Diego Dorta <diego.dorta@nxp.com>
"""
from threading import Thread
from time import sleep
import signal, sys, socket
import gi
gi.require_version("Gst", "1.0")
gi.require_version("GstRtsp", "1.0")
gi.require_version("GstRtspServer", "1.0")
from gi.repository import GLib, GObject, Gst, GstRtsp, GstRtspServer
'''
$ apt-get install libgstreamer1.0-0 gstreamer1.0-plugins-base gstreamer1.0-plugins-good \
                  gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav \
                  gstreamer1.0-doc gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa \
                  gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-qt5 gstreamer1.0-pulseaudio
$ apt-get install libgstrtspserver-1.0-dev gstreamer1.0-rtsp
$ apt-get install gir1.2-gst-rtsp-server-1.0
'''

def establishRtspConnection():
    mcastIP = '225.0.0.1'
    mcastPort = 10000
    message = b'I am alive, watch me!'
    fd = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    fd.sendto(message, (mcastIP, mcastPort))


def runRtspLiveStream(PIPELINE):
    GObject.threads_init()
    Gst.init(None)

    server = GstRtspServer.RTSPServer.new()
    server.props.service = "3000"

    server.attach(None)

    loop = GLib.MainLoop.new(None, False)

    def on_sigint(_sig, _frame):
        print("Got a SIGINT, closing...")
        loop.quit()
    signal.signal(signal.SIGINT, on_sigint)

    def run_main_loop():
        loop.run()

    main_loop_thread = Thread(target=run_main_loop)

    main_loop_thread.start()

    media_factory = GstRtspServer.RTSPMediaFactory.new()
    media_factory.set_launch(PIPELINE)
    media_factory.set_shared(True)
    server.get_mount_points().add_factory("/test", media_factory)
    print("Stream ready at rtsp://127.0.0.1:3000/test")


    while loop.is_running():
        sleep(0.1)


if __name__ == "__main__":


    #establishRtspConnection()    


    #PIPELINE = ("(v4l2src device=/dev/video0 ! video/x-raw,width=640,height=480 ! v4l2h264enc ! rtph264pay name=pay0 pt=96)")
    PIPELINE = ("(v4l2src device=/dev/video0 ! video/x-raw,width=640,height=480 ! v4l2h264enc ! rtph264pay name=pay0 pt=96)")

    runRtspLiveStream(PIPELINE)
    

