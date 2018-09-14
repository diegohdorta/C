#!/usr/bin/env python3
# Requires PyAudio and PySpeech.
 
import speech_recognition as sr
import webbrowser
 
# Record Audio
r = sr.Recognizer()
with sr.Microphone() as source:
    print("Say something!")
    audio = r.listen(source)
 
# Speech recognition using Google Speech Recognition
try:
    # for testing purposes, we're just using the default API key
    # to use another API key, use `r.recognize_google(audio, key="GOOGLE_SPEECH_RECOGNITION_API_KEY")`
    # instead of `r.recognize_google(audio)`

    string = r.recognize_google(audio)

    word = "open"

    if word in string.split():
       print("Success")

       first, second = string.split()
       print("first: " + first)
       print("second: " + second)

       url = "http://www." + second + ".com"

       print("url: " + url)

       webbrowser.get('firefox').open_new(url)

       #webbrowser.open('http://www.' + second + '.com')

       

    print("You said: " + string)
except sr.UnknownValueError:
    print("Google Speech Recognition could not understand audio")
except sr.RequestError as e:
    print("Could not request results from Google Speech Recognition service; {0}".format(e))

