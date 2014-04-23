#! /usr/bin/env python 

import cv2
import numpy as np

class elementBase(object):
	def __init__(self, name):
		self.name = name
		self.image = None
		self.source = None
	
	def set_source(self, source):
		print("%s source was set to %s" %(self.name, source.name))
		self.source = source
	
	def run(self):
		"""Overload this with your own code"""
		pass

class ImageCapture(elementBase):
	def __init__(self, name):
		elementBase.__init__(self, name)
		self.__capture = cv2.VideoCapture(0)
			
	def __get_image(self):
		retval, image = self.__capture.read()
		return image
	
	def run(self):
		self.image = self.__get_image()
		
class ImageDisplay(elementBase):
	def __init__(self, name, title="Default title"):
		elementBase.__init__(self, name)
		self.title = title
		cv2.namedWindow(self.title, cv2.CV_WINDOW_AUTOSIZE)
	
	def run(self):
		cv2.imshow(self.title, self.source.image)

		if cv2.waitKey(20) == 27:
			cv2.destroyWindow(self.title)
			self.capture.release()
			self.running = False	

class ColorTracker(elementBase):
	def __init__(self, name):
		elementBase.__init__(self, name)
		#~ self.source = None
		#~ self.image = None
		self.center_x = None
		self.center_y = None
		self.color_lower = np.array([120, 80, 80],np.uint8)
		self.color_upper = np.array([140, 255, 255],np.uint8)
	
	def set_color(self, color_lower, color_upper):
		self.color_lower = color_lower
		self.color_upper = color_upper
			
	def run(self):
		self.image = self.source.image
		
		# blur image to minimize color noise
		smoothed_img = cv2.GaussianBlur(self.image, (5,5), 0)
		
		# convert colorspace from RGB to HSV(Hue, Saturation, Value) to find
		# the color of interest
		hsv_img = cv2.cvtColor(smoothed_img, cv2.COLOR_BGR2HSV)
		
		# get a binary image of our color of interest
		binary_img = cv2.inRange(hsv_img, self.color_lower, self.color_upper)
					
		# copy binary image as findContours will modify it
		contours_img = binary_img.copy()	
		contours, hierarchy = cv2.findContours(contours_img, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)
		
		# find the largest contour and draw a rectangle around it
		if contours:
			largest_contour=sorted(contours, key=cv2.contourArea)[-1]
			moment = cv2.moments(largest_contour)
			if moment["m00"] > 100:
				x,y,w,h = cv2.boundingRect(largest_contour)
				self.center_x = x+(w/2)
				self.center_y = y+(h/2)
				print("Object center at: x=%i y=%i" %(self.center_x, self.center_y))
				cv2.rectangle(self.image,(x,y),(x+w,y+h),(0,240,240),2)
				cv2.circle(self.image,(self.center_x, self.center_y),2,(0,240,240),2)

class Pipeline(object):
	def __init__(self):
		self.elements = []
	
	def add_elements(self, elements):
		for i in elements:
			self.elements.append(i)
	
	def link_elements(self):
		for i in range(len(self.elements)):
			if i+1 < len(self.elements):
				self.elements[i+1].set_source(self.elements[i])
	
	def run(self):
		while True:
			for i in self.elements:
				i.run()
		
if __name__=="__main__":	
	capture = ImageCapture("capture")
	blue_tracker = ColorTracker("blue_tracker")
	green_tracker = ColorTracker("green_tracker")
	blue_tracker.set_color(np.array([110,50,50],np.uint8),np.array([130,255,255],np.uint8))
	red_tracker = ColorTracker("red_tracker")
	red_tracker.set_color(np.array([0,50,50],np.uint8),np.array([10,255,255],np.uint8))
	green_tracker.set_color(np.array([50, 50, 50],np.uint8),np.array([70, 255, 255],np.uint8))
	display = ImageDisplay("display", title="Color Tracker")
	pipeline = Pipeline()
	pipeline.add_elements([capture, blue_tracker, green_tracker, red_tracker, display])
	pipeline.link_elements()
	pipeline.run()
