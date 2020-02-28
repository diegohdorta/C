#!/usr/bin/env python3
from flask import Flask, render_template, Response
import os, cv2, face_recognition as fr

path = "media/"

class FaceRecognition(object):
    def __init__(self):
        self.vext = [".jpg", ".png"]
        self.labels = []
        self.encodings = []
        self.v4l2_str = ""
        self.cam = 0
        self.faceLocations = []
        self.faceEncodings = []
        self.faceNames = []
        self.processFrame = True
        
    def getFaces(self):
        for f in os.listdir(path):
            fext = os.path.splitext(f)[1]
            if (fext) not in self.vext:
                continue
            self.labels.append(os.path.splitext(f)[0])
            face = fr.load_image_file(path + f)
            self.encodings.append(fr.face_encodings(face)[0])
            
    def setting_mipi_cam(self, width, height):
        self.v4l2_str = ("v4l2src ! video/x-raw,width={},height={} !"
                " appsink").format(width, height)

    def openMipiCam(self):
#        self.cam = cv2.VideoCapture(0)
        self.cam = cv2.VideoCapture(self.v4l2_str)
        
    def getFrame(self):
        success, frame = self.cam.read()        
        sFrame = cv2.resize(frame, (0, 0), fx = 0.25, fy = 0.25)
        rgb_sFrame = sFrame[:, :, ::-1]
        if (self.processFrame):
            self.faceLocations = fr.face_locations(rgb_sFrame)
            self.faceEncodings = fr.face_encodings(rgb_sFrame, self.faceLocations)
            self.faceNames = []
            for fe in self.faceEncodings:
                m = fr.compare_faces(self.encodings, fe)
                name = "Unknown"
                if (True) in m:
                    md = m.index(True)
                    name = self.labels[md]
                self.faceNames.append(name)
        self.processFrame = not self.processFrame
        
        for (top, right, bottom, left), name in zip(self.faceLocations, self.faceNames):
            top *= 4
            right *= 4
            bottom *= 4
            left *= 4
            cv2.rectangle(frame, (left, top), (right, bottom), (0, 0, 255), 2)
            cv2.rectangle(frame, (left, bottom - 35), (right, bottom), (0, 0, 255), cv2.FILLED)
            font = cv2.FONT_HERSHEY_DUPLEX
            cv2.putText(frame, name, (left + 6, bottom - 6), font, 1.0, (255, 255, 255), 1)        
        ret, jpeg = cv2.imencode('.jpg', frame)        
        return jpeg.tobytes()

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

def gen(demo):
    demo = FaceRecognition()
    demo.getFaces()
    demo.setting_mipi_cam(640, 480)
    demo.openMipiCam()

    while True:
        frame = demo.getFrame()
        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n\r\n')

@app.route('/video_feed')
def video_feed():
    return Response(gen(FaceRecognition()),
                mimetype='multipart/x-mixed-replace; boundary=frame')

if __name__ == '__main__':
    app.run(host='0.0.0.0', debug=True)     
