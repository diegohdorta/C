import cv2
import re
import time
import numpy as np
from tflite_runtime.interpreter import Interpreter

MODEL_FILE = 'detect.tflite'
LABEL_FILE = 'coco_labels.txt'
THRESHOLD = 0.4

MODEL_SIZE = 300

CAMERA_WIDTH = 640
CAMERA_HEIGHT = 480

def load_labels(path):
    with open(path, 'r', encoding='utf-8') as f:
        lines = f.readlines()
        labels = {}
        for row_number, content in enumerate(lines):
            pair = re.split(r'[:\s]+', content.strip(), maxsplit=1)
            if len(pair) == 2 and pair[0].strip().isdigit():
                labels[int(pair[0])] = pair[1].strip()
            else:
                labels[row_number] = pair[0].strip()
    return labels
  
def set_input_tensor(interpreter, img):
    tensor_index = interpreter.get_input_details()[0]['index']
    input_tensor = interpreter.tensor(tensor_index)()[0]
    input_tensor[:, :] = img

def get_output_tensor(interpreter, index):
    output_details = interpreter.get_output_details()[index]
    tensor = np.squeeze(interpreter.get_tensor(output_details['index']))
    return tensor

def detect_objects(interpreter, img, threshold):
    set_input_tensor(interpreter, img)
    interpreter.invoke()

    boxes = get_output_tensor(interpreter, 0)
    classes = get_output_tensor(interpreter, 1)
    scores = get_output_tensor(interpreter, 2)
    count = int(get_output_tensor(interpreter, 3))

    results = []
    for i in range(count):
        if scores[i] >= threshold:
            result = {
                'bounding_box': boxes[i],
                'class_id': classes[i],
                'score': scores[i]
            }
            results.append(result)
    return results 

def annotate_objects(img, results, labels):
    for obj in results:
        ymin, xmin, ymax, xmax = obj['bounding_box']
        xmin = int(xmin * CAMERA_WIDTH)
        xmax = int(xmax * CAMERA_WIDTH)
        ymin = int(ymin * CAMERA_HEIGHT)
        ymax = int(ymax * CAMERA_HEIGHT)

        cv2.putText(img, labels[int(obj['class_id'])] + " " + str('%.1f'%(obj['score']*100)) + "%", (xmin, int(ymax + .05 * xmax)), cv2.FONT_HERSHEY_SIMPLEX, 1.0, (0, 0, 255))

        cv2.rectangle(img, (xmin, ymax), (xmax, ymin), (0, 0, 255), thickness=2)

def main():
    labels = load_labels(LABEL_FILE)

    interpreter = Interpreter(MODEL_FILE)
    interpreter.allocate_tensors()
    _, input_height, input_width, _ = interpreter.get_input_details()[0]['shape']

    video_cap = cv2.VideoCapture("v4l2src ! video/x-raw,width=640,height=480 ! appsink")

    while True:
        ret, img = video_cap.read()
        rows, cols, channels = img.shape
        resized_img = cv2.resize(img, (MODEL_SIZE, MODEL_SIZE))

        start_time = time.monotonic()
        results = detect_objects(interpreter, resized_img, THRESHOLD)
        elapsed_ms = (time.monotonic() - start_time) * 1000
        print("Inference took " + str(int(elapsed_ms)) + " ms")
        
        annotate_objects(img, results, labels)

        cv2.imshow('Video', img)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cv2.destroyAllWindows()

if __name__ == '__main__':
    main()
