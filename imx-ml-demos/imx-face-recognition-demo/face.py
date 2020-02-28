#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Diego Dorta <diego.dorta@nxp.com>
"""
import face_recognition as fr
import PIL as p
import os, os.path, cv2

path = "media/"

def open_cam(type, width, height):
    v4l2_str = ("v4l2src ! video/x-raw,width={},height={} !"
                " appsink").format(width, height)
    return cv2.VideoCapture(v4l2_str if (type) else 0)

def reading_data(images=[], labels=[], encodings=[]):
    valid_ext = [".jpg", ".png"]
    for photo in os.listdir(path):
        photo_ext = os.path.splitext(photo)[1]
        if (photo_ext.lower() not in valid_ext):
            continue
        labels.append(os.path.splitext(photo)[0])    
        face = fr.load_image_file(path + photo)
        encodings.append(fr.face_encodings(face)[0])
    return labels, encodings

def main():
    labels, encodings = reading_data()
    face_locations = []
    face_encodings = []
    face_names = []
    process_this_frame = True
    input_cam = open_cam(False, 640, 480)

    while True:
        ret, frame = input_cam.read()
        small_frame = cv2.resize(frame, (0, 0), fx=0.25, fy=0.25)
        rgb_small_frame = small_frame[:, :, ::-1]
        
        if process_this_frame:
            face_locations = fr.face_locations(rgb_small_frame)
            face_encodings = fr.face_encodings(rgb_small_frame, face_locations)
            face_names = []
            for face_encoding in face_encodings:
                matches = fr.compare_faces(encodings, face_encoding)
                name = "Unknown"
                if True in matches:
                    first_match_index = matches.index(True)
                    name = labels[first_match_index]
                face_names.append(name)
        process_this_frame = not process_this_frame

        for (top, right, bottom, left), name in zip(face_locations, face_names):
            top *= 4
            right *= 4
            bottom *= 4
            left *= 4
            cv2.rectangle(frame, (left, top), (right, bottom), (0, 0, 255), 2)
            cv2.rectangle(frame, (left, bottom - 35), (right, bottom), (0, 0, 255), cv2.FILLED)
            font = cv2.FONT_HERSHEY_DUPLEX
            cv2.putText(frame, name, (left + 6, bottom - 6), font, 1.0, (255, 255, 255), 1)
        cv2.imshow('Video', frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    input_cam.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
