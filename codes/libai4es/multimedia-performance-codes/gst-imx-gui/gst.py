#!/usr/bin/env python3
import sys, os
import gi
gi.require_version('Gst', '1.0')
gi.require_version('Gtk', '3.0')
gi.require_version('GstVideo', '1.0')
from gi.repository import Gst, GObject, Gtk
from gi.repository import GObject, Gst, GstVideo

class gtkStreamerWindow(Gtk.Window):
    def __init__(self):
        self.appGtkWindow = Gtk.Window(Gtk.WindowType.TOPLEVEL)
        self.appGtkWindow.set_title("NXP - Realtime RTSP Player")
        self.appGtkWindow.set_default_size(640, 480)
        self.appGtkWindow.connect("destroy", Gtk.main_quit)

        containerForAll = Gtk.VBox()
        self.appGtkWindow.add(containerForAll)

        self.movieWindow= Gtk.DrawingArea()
        containerForAll.add(self.movieWindow)

        containerForButtons = Gtk.HBox(True)
        containerForRadioButtons = Gtk.HBox(True)
        containerForButtons.set_border_width(5)
        containerForButtons.pack_start(Gtk.Label(), False, False, 0)
        containerForAll.pack_start(containerForButtons, False, False, 0)
     
        self.buttonStart = Gtk.Button("Start")
        self.buttonOpenGL = Gtk.Button("OpenGL")
        self.buttonQuit = Gtk.Button("Quit")

        self.buttonStart.connect("clicked", self.start)
        self.buttonOpenGL.connect("clicked", self.live)
        self.buttonQuit.connect("clicked", self.exit)
        
        containerForButtons.pack_start(self.buttonStart, False, False, 0)
        containerForButtons.pack_start(self.buttonOpenGL, False, False, 0)
        containerForButtons.pack_start(self.buttonQuit, False, False, 0)

        containerForButtons.add(Gtk.Label())
        self.appGtkWindow.show_all()

    def start(self, w):
        if (self.buttonStart.get_label() == "Start"):
            self.buttonStart.set_label("Stop")
            self.buttonOpenGL.set_sensitive(False)
            self.player = Gst.parse_launch ("v4l2src ! autovideosink")
            '''
            Create bus to get events from GStreamer pipeline
            '''            
            bus = self.player.get_bus()
            bus.add_signal_watch()
            bus.connect('message::eos', self.on_eos)
            bus.connect('message::error', self.on_error)
            '''
            This is needed to make the video output in our movieWindow:
            '''
            bus.enable_sync_message_emission()
            bus.connect("sync-message::element", self.on_sync_message)                
            self.player.set_state(Gst.State.PLAYING)
        else:
            self.player.set_state(Gst.State.NULL)
            self.buttonStart.set_label("Start")
            self.buttonOpenGL.set_sensitive(True)
            
    def live(self, w):
        if (self.buttonOpenGL.get_label() == "OpenGL"):
            self.buttonOpenGL.set_label("Stop")
            self.buttonStart.set_sensitive(False)
            self.player = Gst.parse_launch ("v4l2src ! glimagesink")
            '''
            Create bus to get events from GStreamer pipeline
            '''            
            bus = self.player.get_bus()
            bus.add_signal_watch()
            bus.connect('message::eos', self.on_eos)
            bus.connect('message::error', self.on_error)
            '''
            This is needed to make the video output in our movieWindow:
            '''
            bus.enable_sync_message_emission()
            bus.connect("sync-message::element", self.on_sync_message)                
            self.player.set_state(Gst.State.PLAYING)
        else:
            self.player.set_state(Gst.State.NULL)
            self.buttonOpenGL.set_label("OpenGL")
            self.buttonStart.set_sensitive(True)
            
    def exit(self, widget, data=None):
        Gtk.main_quit()

    def on_sync_message(self, bus, msg):
        if (msg.get_structure().get_name() == 'prepare-window-handle'):
            #msg.src.set_window_handle(self.movieWindow.get_property('window')._init_widget())
            msg.src.set_window_handle(self.movieWindow.get_property('window').get_xid())
            
            
    def on_eos(self, bus, msg):
        self.player.set_state(Gst.State.NULL)
        print('on_eos(): seeking to start of video')
        #self.pipeline.seek_simple(Gst.Format.TIME, Gst.SeekFlags.FLUSH | Gst.SeekFlags.KEY_UNIT, 0) ??

    def on_error(self, bus, msg):
        self.player.set_state(Gst.State.NULL)
        print('on_error():', msg.parse_error())

if __name__ == "__main__":

    Gst.init(None)
    gtkStreamerWindow()
    GObject.threads_init()
    Gtk.main()


#    def on_message(self, bus, message):
#        t = message.type
#        if (t == Gst.MessageType.EOS):
#            self.player.set_state(Gst.State.NULL)
#            self.button.set_label("Start")
#        elif (t == Gst.MessageType.ERROR):
#            err, debug = message.parse_error()
#            print ("Error: %s" % err, debug)
#            self.player.set_state(Gst.State.NULL)
#            self.button.set_label("Start")

#    def on_sync_message(self, bus, message):
#        struct = message.get_structure()
#        if not struct:
#            return
#        message_name = struct.get_name()
#        print(message_name)
#        if message_name == "prepare-window-handle":
#            # Assign the viewport
#            imagesink = message.src
#            print(message.src)
#            imagesink.set_property("force-aspect-ratio", True)
#            imagesink.set_window_handle(self.movie_window.get_property('window').get_xid())




        #LINHA CERTA DO SERVER
        #gst-variable-rtsp-server -p 9001 -u "v4l2src device=/dev/video0 ! video/x-raw, width=640, height=480 ! v4l2h264_enc ! rtph264pay name=pay0 pt=96"

        # Linha certa do client
        #gst-launch-1.0 rtspsrc location=rtsp://10.29.244.97:9001/stream latency          =100 buffer-mode=slave ! rtph264depay ! avdec_h264 ! autovideosink sync=false




# Set up the gstreamer pipeline
#gst-launch-1.0 rtspsrc location=rtsp://10.29.244.97:9001/stream latency=100 buf          fer-mode=slave ! queue max-size-buffers=0 ! rtph264depay ! vpudec ! v4l2sink syn          c=false
#self.player = Gst.parse_launch ("rtspsrc location=rtsp://"+sys.argv[1]+"/profile?token=media_profile1&SessionTimeout=600000 latency=0 droponlatency=1 ! rtph264          depay ! decodebin ! videoconvert ! autovideosink")




#SERVER

#gst-launch-1.0 rtspsrc location=rtsp://10.29.244.97:9001/stream ! rtph264depay           ! avdec_h264  ! autovideosink

#gst-variable-rtsp-server -p 9001 -u "v4l2src device=/dev/video0 ! capsfilter ca          ps='video/x-raw, width=640, height=480' ! v4l2h264_enc ! rtph264pay name=pay0 pt          =96"

#self.player = Gst.parse_launch ("rtspsrc location=rtsp://10.29.244.97:9001/stre          am latency=0 droponlatency=1 ! rtph264depay ! avdec_h264 ! autovideosink")
#self.player = Gst.parse_launch ("v4l2src ! autovideosink")



#   buttonNoOpenGL =Gtk.RadioButton.new_with_label_from_widget(None, "No OpenGL")
#        buttonNoOpenGL.connect("toggled", self.on_button_toggled, "1")
#        containerForAll.pack_start(buttonNoOpenGL, False, False, 0)

 #       buttonOpenGL = Gtk.RadioButton.new_from_widget(buttonNoOpenGL)
 #       buttonOpenGL.set_label("OpenGL")
 #       buttonOpenGL.connect("toggled", self.on_button_toggled, "2")
 #       containerForAll.pack_start(buttonOpenGL, False, False, 0)

  #      buttonOpenGL1 = Gtk.RadioButton.new_from_widget(buttonNoOpenGL)
  #      buttonOpenGL1.set_label("OpenGL1")
  #      buttonOpenGL1.connect("toggled", self.on_button_toggled, "3")
  #      containerForAll.pack_start(buttonOpenGL1, False, False, 0)

#
#               containerForAll.pack_start(containerForRadioButtons, False, False, 0)
#        
#                containerForRadioButtons.set_border_width(10)
#        containerForRadioButtons.pack_start(Gtk.Label(), False, False, 0)
        
        #containerForRadioButtons.pack_start(self.buttonAA, False, False, 0)


########################## OUTRO CODIGO

#from os import path
#import gi
#gi.require_version('Gst', '1.0')
#gi.require_version('Gtk', '3.0')
#gi.require_version('GdkX11', '3.0')
#gi.require_version('GstVideo', '1.0')
#from gi.repository import GObject, Gst, Gtk

# Needed for get_xid(), set_window_handle()
#from gi.repository import GdkX11, GstVideo

# Needed for timestamp on file output
#from datetime import datetime
#GObject.threads_init()
#Gst.init(None)
#location = '/dev/video0'

#class Player(Gtk.Window):
#    def __init__(self):
#        Gtk.Window.__init__(self, title="Liveview")
#        self.connect('destroy', self.quit)
#        self.set_default_size(800, 450)

        # Create DrawingArea for video widget
#        self.drawingarea = Gtk.DrawingArea()

        # Create a grid for the DrawingArea and buttons
#        grid = Gtk.Grid()
#        self.add(grid)
#        grid.attach(self.drawingarea, 0, 1, 2, 1)
#        # Needed or else the drawing area will be really small (1px)
#        self.drawingarea.set_hexpand(True)
#        self.drawingarea.set_vexpand(True)

        # Quit button
#        quit = Gtk.Button(label="Quit")
#        quit.connect("clicked", Gtk.main_quit)
#        grid.attach(quit, 0, 0, 1, 1)

        # Record/Stop button
#        self.record = Gtk.Button(label="Record")
#        self.record.connect("clicked", self.record_button)
#        grid.attach(self.record, 1, 0, 1, 1)

        # Create GStreamer pipeline
#        self.pipeline = Gst.parse_launch("v4l2src device=" + location + " ! tee name=tee ! queue name=videoqueue ! deinterlace ! xvimagesink")

        # Create bus to get events from GStreamer pipeline
#        bus = self.pipeline.get_bus()
#        bus.add_signal_watch()
#        bus.connect('message::eos', self.on_eos)
#        bus.connect('message::error', self.on_error)

        # This is needed to make the video output in our DrawingArea:
#        bus.enable_sync_message_emission()
#        bus.connect('sync-message::element', self.on_sync_message)

#    def run(self):
#        self.show_all()
#        self.xid = self.drawingarea.get_property('window').get_xid()
#        self.pipeline.set_state(Gst.State.PLAYING)
#        Gtk.main()

#    def quit(self, window):
#        self.pipeline.set_state(Gst.State.NULL)
#        Gtk.main_quit()

#    def on_sync_message(self, bus, msg):
#        if msg.get_structure().get_name() == 'prepare-window-handle':
#            print('prepare-window-handle')
#            msg.src.set_window_handle(self.xid)

#    def on_eos(self, bus, msg):
#        print('on_eos(): seeking to start of video')
#        self.pipeline.seek_simple(
#            Gst.Format.TIME,
#            Gst.SeekFlags.FLUSH | Gst.SeekFlags.KEY_UNIT,
#            0
#        )

#    def on_error(self, bus, msg):
#        print('on_error():', msg.parse_error())

#    def start_record(self):
        # Filename (current time)
#        filename = datetime.now().strftime("%Y-%m-%d_%H.%M.%S") + ".avi"
#        print(filename)
#        self.recordpipe = Gst.parse_bin_from_description("queue name=filequeue ! jpegenc ! avimux ! filesink location=" + filename, True)
#        self.pipeline.add(self.recordpipe)
#        self.pipeline.get_by_name("tee").link(self.recordpipe)
#        self.recordpipe.set_state(Gst.State.PLAYING)

#    def stop_record(self):
#        filequeue = self.recordpipe.get_by_name("filequeue")
#        filequeue.get_static_pad("src").add_probe(Gst.PadProbeType.BLOCK_DOWNSTREAM, self.probe_block)
#        self.pipeline.get_by_name("tee").unlink(self.recordpipe)
#        filequeue.get_static_pad("sink").send_event(Gst.Event.new_eos())
#        print("Stopped recording")

#    def record_button(self, widget):
#        if self.record.get_label() == "Record":
#            self.record.set_label("Stop")
#            self.start_record()
#        else:
#            self.stop_record()
#           self.record.set_label("Record")

#    def probe_block(self, pad, buf):
#        print("blocked")
#        return True

#p = Player()
#p.run()

