### Sagan 0.1 ### Code for reading tests automatic.
# Diego Dorta <diegohdorta@gmail.com>

import sys
import cv2
import numpy as np
import math

WIDTH = 2
HEIGHT = 30

def verify_number_of_answers(n):

	if (n != 30):
		sys.exit("Wrong number of questions answered! Try to correct manually!")

def set_parameters():

	params = cv2.SimpleBlobDetector_Params()

	params.minThreshold = 30;
	params.maxThreshold = 200;
	 
	params.filterByArea = True
	params.minArea = 70
	 
	params.filterByCircularity = True
	params.minCircularity = 0.1
	 
	params.filterByConvexity = True
	params.minConvexity = 0.87
	 
	params.filterByInertia = True
	params.minInertiaRatio = 0.01

	return params

def get_answer_key():

	image = cv2.imread("answer-key/answer-key.png", cv2.CV_LOAD_IMAGE_GRAYSCALE)
	image = image[65:323, 145:554]
	ret, image = cv2.threshold(image, 0, 255, cv2.cv.CV_THRESH_BINARY)

	detector = cv2.SimpleBlobDetector(set_parameters())
	keypoints = detector.detect(image)

	n_answers = len(keypoints)
	verify_number_of_answers(n_answers)

	answer_keys = [[0 for x in range(WIDTH)] for y in range(HEIGHT)] 
	
	for p in range (0, n_answers):

		x = keypoints[p].pt[0]
		y = keypoints[p].pt[1]

		answer_keys[p][0] = math.floor(x)
		answer_keys[p][1] = math.floor(y)

	keypoints_red = cv2.drawKeypoints(image, keypoints, np.array([]), (0,0,255), cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
	cv2.imshow("points", keypoints_red)
	cv2.imwrite("crops/crop_image_answer_key.png",image)
	cv2.waitKey(2000)

	return answer_keys

def get_test():

	image = cv2.imread("tests/test.png", cv2.CV_LOAD_IMAGE_GRAYSCALE)
	image = image[65:323, 145:554]
	ret, image = cv2.threshold(image, 0, 255, cv2.cv.CV_THRESH_BINARY)

	detector = cv2.SimpleBlobDetector(set_parameters())
	keypoints = detector.detect(image)

	n_answers = len(keypoints)
	verify_number_of_answers(n_answers)

	test = [[0 for x in range(WIDTH)] for y in range(HEIGHT)] 
	
	for p in range (0, n_answers):

		x = keypoints[p].pt[0]
		y = keypoints[p].pt[1]

		test[p][0] = math.floor(x)
		test[p][1] = math.floor(y)

	keypoints_red = cv2.drawKeypoints(image, keypoints, np.array([]), (0,0,255), cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
	cv2.imshow("points", keypoints_red)
	cv2.imwrite("crops/crop_image_test.png",image)
	cv2.waitKey(2000)

	return test

if __name__ == "__main__":
	
	answer_keys = get_answer_key()
	test = get_test()

	right_answers = 0	

	# Implement a logic for correcting the tests.

	for x in range (1, 30):
		
		for y in range (1, 2): 
	
			if (answer_keys[x][y] == test[x][y]):
			
			#print "Answer Key: ", answer_keys[x][y]
			#print test[x][y]
				right_answers += 1
				



	print "Number of right answers: ", right_answers

	#print "Answer Key Coordinates: ", answer_keys
	#print "Test answers: ", test







