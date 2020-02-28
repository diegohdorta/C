import cv2
import time
import numpy as np
from tflite_runtime.interpreter import Interpreter

def set_input_tensor(interpreter, image):
    tensor_index = interpreter.get_input_details()[0]['index']
    input_tensor = interpreter.tensor(tensor_index)()[0]
    input_tensor[:, :] = image

def get_output_tensor(interpreter, index):
    output_details = interpreter.get_output_details()[index]
    tensor = np.squeeze(interpreter.get_tensor(output_details['index']))
    return tensor

def detect_objects(interpreter, image, threshold):
    set_input_tensor(interpreter, image)
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

def annotate_objects(image, results, labels, className):
    for obj in results:
        ymin, xmin, ymax, xmax = obj['bounding_box']
        xmin = int(xmin * 640)
        xmax = int(xmax * 640)
        ymin = int(ymin * 480)
        ymax = int(ymax * 480)

        cv2.putText(image, className[int(obj['class_id'])-1] + " " + str('%.1f'%(obj['score']*100)) + "%", (xmin, int(ymax + .05 * xmax)), cv2.FONT_HERSHEY_SIMPLEX, 1.0, (0, 0, 255))

        cv2.rectangle(image, (xmin, ymax), (xmax, ymin), (0, 0, 255), thickness=2)

def main():
    model = 'detect.tflite'
    labels = 'coco_labels.txt'
    lin = open(labels).read().strip().split("\n")
    className = [r[r.find(" ") + 1:].split(",")[0] for r in lin]
    threshold = 0.4

    interpreter = Interpreter(model)
    interpreter.allocate_tensors()
    _, input_height, input_width, _ = interpreter.get_input_details()[0]['shape']

    video_cap = cv2.VideoCapture("v4l2src ! video/x-raw,width=640,height=480 ! appsink")

    while True:
        ret, img = video_cap.read()
        rows, cols, channels = img.shape
        resized_img = cv2.resize(img, (300, 300))

        start_time = time.monotonic()
        results = detect_objects(interpreter, resized_img, threshold)
        elapsed_ms = (time.monotonic() - start_time) * 1000
        
        annotate_objects(img, results, labels, className)

        cv2.imshow('Video', img)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cv2.destroyAllWindows()

if __name__ == '__main__':
    main()
