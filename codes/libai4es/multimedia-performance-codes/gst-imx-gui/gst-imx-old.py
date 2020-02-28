#!/usr/bin/env python3
import sys, os
import gi
gi.require_version('Gst', '1.0')
from gi.repository import Gst, GObject, Gtk
from gi.repository import GObject, Gst, GstVideo

#        self.button2.set_sensitive(False)

class gtkStreamerWindow(Gtk.Window):
    def __init__(self):
        self.appGtkWindow = Gtk.Window(Gtk.WindowType.TOPLEVEL)
        self.appGtkWindow.set_title("NXP - Realtime RTSP Player")
        self.appGtkWindow.set_default_size(640, 512)
        self.appGtkWindow.connect("destroy", Gtk.main_quit)

        containerForAll = Gtk.VBox()
        self.appGtkWindow.add(containerForAll)

        self.movie_window = Gtk.DrawingArea()
        containerForAll.add(self.movie_window)

        containerForButtons = Gtk.HBox(True)
        containerForRadioButtons = Gtk.HBox(True)

        containerForButtons.set_border_width(10)
        containerForButtons.pack_start(Gtk.Label(), False, False, 0)

        containerForRadioButtons.set_border_width(1)
        containerForRadioButtons.pack_start(Gtk.Label(), False, False, 0)

        containerForAll.pack_start(containerForButtons, False, False, 0)
        containerForAll.pack_start(containerForRadioButtons, False, False, 0)

        buttonNoOpenGL = Gtk.RadioButton.new_with_label_from_widget(None, "No OpenGL")
        buttonNoOpenGL.connect("toggled", self.on_button_toggled, "1")
        containerForAll.pack_start(buttonNoOpenGL, False, False, 0)

        buttonOpenGL = Gtk.RadioButton.new_from_widget(buttonNoOpenGL)
        buttonOpenGL.set_label("OpenGL")
        buttonOpenGL.connect("toggled", self.on_button_toggled, "2")
        containerForAll.pack_start(buttonOpenGL, False, False, 0)
        
        buttonOpenGL1 = Gtk.RadioButton.new_from_widget(buttonNoOpenGL)
        buttonOpenGL1.set_label("OpenGL1")
        buttonOpenGL1.connect("toggled", self.on_button_toggled, "3")
        containerForAll.pack_start(buttonOpenGL1, False, False, 0)


        self.button = Gtk.Button("Start")
        self.button2 = Gtk.Button("Quit")
        self.buttonAA = Gtk.Button("Live RSTP")


        self.button.connect("clicked", self.start_stop)
        self.button2.connect("clicked", self.exit)
        self.buttonAA.connect("clicked", self.aaa)

        containerForButtons.pack_start(self.button, False, False, 0)
        containerForButtons.pack_start(self.button2, False, False, 0)
        containerForRadioButtons.pack_start(self.buttonAA, False, False, 0)


        containerForButtons.add(Gtk.Label())
        self.appGtkWindow.show_all()
        
        
        #LINHA CERTA DO SERVER
        #gst-variable-rtsp-server -p 9001 -u "v4l2src device=/dev/video0 ! video/x-raw, width=640, height=480 ! v4l2h264_enc ! rtph264pay name=pay0 pt=96"

        # Linha certa do client
        #gst-launch-1.0 rtspsrc location=rtsp://10.29.244.159:9001/stream latency=100 buffer-mode=slave ! rtph264depay ! avdec_h264 ! autovideosink sync=false
       # render-rectangle='<0, 0, 640, 480>'

        #self.player = Gst.parse_launch ("rtspsrc location=rtsp://10.29.244.159:9001/stream  latency=100 buffer-mode=slave ! rtph264depay ! v4l2h264dec ! imxvideoconvert_g2d ! glimagesink sync=false")
        
        
        self.player = Gst.parse_launch ("rtspsrc location=rtsp://10.29.244.159:9001/stream ! rtph264depay ! avdec_h264 ! autovideosink sync=false")
        
        bus = self.player.get_bus()
        bus.add_signal_watch()
        bus.enable_sync_message_emission()
        bus.connect("message", self.on_message)
        bus.connect("sync-message::element", self.on_sync_message)

    def start_stop(self, w):
        if self.button.get_label() == "Start":
            self.button.set_label("Stop")
            self.player.set_state(Gst.State.PLAYING)
        else:
            self.player.set_state(Gst.State.NULL)
            self.appGtkWindow.clear()
            self.button.set_label("Start")

    def aaa(self, w):
        print("aaa")

    def on_button_toggled(self, button, name):
        if button.get_active():
            state = "on"
        else:
            state = "off"
        print("Button", name, "was turned", state)


    def exit(self, widget, data=None):
        Gtk.main_quit()

    def on_message(self, bus, message):
        t = message.type
        if t == Gst.MessageType.EOS:
            self.player.set_state(Gst.State.NULL)
            self.button.set_label("Start")
        elif t == Gst.MessageType.ERROR:
            err, debug = message.parse_error()
            print ("Error: %s" % err, debug)
            self.player.set_state(Gst.State.NULL)
            self.button.set_label("Start")

    def on_sync_message(self, bus, message):
        struct = message.get_structure()
        if not struct:
            return
        message_name = struct.get_name()
        if message_name == "prepare-window-handle":
            # Assign the viewport
            imagesink = message.src
            imagesink.set_property("force-aspect-ratio", True)
            imagesink.set_window_handle(self.movie_window.get_property('window').get_xid())

if __name__ == "__main__":

    Gst.init(None)
    gtkStreamerWindow()
    GObject.threads_init()
    Gtk.main()
    
    
    

# Set up the gstreamer pipeline
#gst-launch-1.0 rtspsrc location=rtsp://10.29.244.97:9001/stream latency=100 buffer-mode=slave ! queue max-size-buffers=0 ! rtph264depay ! vpudec ! v4l2sink sync=false
#self.player = Gst.parse_launch ("rtspsrc location=rtsp://"+sys.argv[1]+"/profile?token=media_profile1&SessionTimeout=600000 latency=0 droponlatency=1 ! rtph264depay ! decodebin ! videoconvert ! autovideosink")



    
#SERVER

#gst-launch-1.0 rtspsrc location=rtsp://10.29.244.97:9001/stream ! rtph264depay ! avdec_h264  ! autovideosink

#gst-variable-rtsp-server -p 9001 -u "v4l2src device=/dev/video0 ! capsfilter caps='video/x-raw, width=640, height=480' ! v4l2h264_enc ! rtph264pay name=pay0 pt=96"

#self.player = Gst.parse_launch ("rtspsrc location=rtsp://10.29.244.97:9001/stream latency=0 droponlatency=1 ! rtph264depay ! avdec_h264 ! autovideosink")
#self.player = Gst.parse_launch ("v4l2src ! autovideosink")
