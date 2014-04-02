#! /usr/bin/env python 

import cv2
import numpy as np

class ColorContours(object):
	def __init__(self):
		cv2.namedWindow("Color Contours", cv2.CV_WINDOW_AUTOSIZE)
		self.capture = cv2.VideoCapture(0)
		self.running = True
		self.color_lower = np.array([120, 80, 80],np.uint8)
		self.color_upper = np.array([140, 255, 255],np.uint8)
	
	def set_color(self, color_lower, color_upper):
		self.color_lower = color_lower
		self.color_upper = color_upper
		
	def get_image(self):
		retval, image = self.capture.read()
		return image
	
	def run(self):
		while self.running:
			image = self.get_image()
			
			# blur image to minimize color noise
			smoothed_img = cv2.GaussianBlur(image, (5,5), 0)
			
			# convert colorspace from RGB to HSV(Hue, Saturation, Value) to find
			# the color of interest
			hsv_img = cv2.cvtColor(smoothed_img, cv2.COLOR_BGR2HSV)
			
			# get a binary image of our color of interest
			binary_img = cv2.inRange(hsv_img, self.color_lower, self.color_upper)
						
			# copy binary image as findContours will modify it
			contours_img = binary_img.copy()	
			contours, hierarchy = cv2.findContours(contours_img, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)
			
			cv2.drawContours(image, contours, -1, (0,255,0), 3)
						
			# Show image
			cv2.imshow("Color Contours", image)

			if cv2.waitKey(20) == 27:
				cv2.destroyWindow("Color Contours")
				self.capture.release()
				self.running = False

if __name__=="__main__":
	color_contours=ColorContours()
	color_contours.run()
