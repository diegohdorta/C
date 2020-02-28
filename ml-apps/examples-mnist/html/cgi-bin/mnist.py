#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Copyright © 2017 Arm Ltd. All rights reserved.

04/16/2019 Diego Dorta <diego.dorta@nxp.com>

This example was copied from ARM examples respecting its rights. All the
modified parts below are according to Apache License 2.0.

This example is only for training purposes, the code below has only a few
modifications in order to get a better overview of the Mnist data example.

CGI script that accepts image urls and feeds them into a ML classifier.
Results are returned in JSON format. 

Reference:
https://github.com/ARM-software/Tool-Solutions
"""
import io, subprocess, json, sys, os, re
import base64
import numpy as np
from PIL import Image

res = {"result": 0,
       "data": [], 
       "error": ''}
try:
    if os.environ["REQUEST_METHOD"] == "POST":
        data = sys.stdin.read(int(os.environ["CONTENT_LENGTH"]))
        img_str = re.search(r'base64,(.*)', data).group(1)
        image_bytes = io.BytesIO(base64.b64decode(img_str))
        im = Image.open(image_bytes)
        im = im.resize((28,28))
        arr = np.array(im)[:,:,0:1]
        arr = (255 - arr)            
        np.savetxt("image.txt", arr.reshape(784), fmt='%d')
        try:
            '''
            Accelleration: 0 = CPU Unoptimized
                           1 = CPU Accelerated
                           2 = GPU Accelerated
            Model:         0 = Simple (Low accuracy)
                           1 = Optimized (Higher accuracy)
            '''
            completed = subprocess.run(['./3-example', 'image.txt'],
                                        stderr=subprocess.PIPE, check=True)
        except subprocess.CalledProcessError as err:
            print('ERROR:', err, file=sys.stderr)
        output_lines = completed.stderr.decode('utf-8').splitlines()
        is_result = True
        try:
            is_result = (type(float(output_lines[0].split()[0])) == float)
        except ValueError as err:
            is_result = False
        finally:
            predictions = output_lines[int(not(is_result))].split()
        res['result'] = 1
        try:
            results = [float(num) for num in predictions]
        except ValueError as err:
            print('ERROR:', err, file=sys.stderr)
        maxpos = results.index(max(results))
        probs = [x/max(results) for x in results]
        res['data'] = probs
except Exception as e:
    res['error'] = str(e)
    
print("Content-type: application/json")
print("") 
print(json.dumps(res))
