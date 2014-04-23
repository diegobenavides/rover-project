#! /usr/bin/env python 

import cv2
import numpy as np

class ColorTracker(object):
	def __init__(self):
		cv2.namedWindow("Color Tracker", cv2.CV_WINDOW_AUTOSIZE)
		self.capture = cv2.VideoCapture(1)
		self.running = True
		self.center_x = None
		self.center_y = None
		self.color_lower = np.array([120, 80, 80],np.uint8)
		self.color_upper = np.array([140, 255, 255],np.uint8)
	
	def set_color(self, color_lower, color_upper):
		self.color_lower = color_lower
		self.color_upper = color_upper
		
	def get_image(self):
		retval, image = self.capture.read()
		return image
	
	def get_Xvalue(self):
		return self.center_x
	
	def get_Yvalue(self):
		return self.center_y		
	
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
			
			# find the largest contour and draw a rectangle around it
			if contours:
				largest_contour=sorted(contours, key=cv2.contourArea)[-1]
				moment = cv2.moments(largest_contour)
				if moment["m00"] > 100:
					x,y,w,h = cv2.boundingRect(largest_contour)
					self.center_x = x+(w/2)
					self.center_y = y+(h/2)
					print("Object center at: x=%i y=%i" %(self.center_x, self.center_y))
					cv2.rectangle(image,(x,y),(x+w,y+h),(0,255,0),2)
					cv2.circle(image,(self.center_x, self.center_y),2,(0,0,255),2)
											
			cv2.imshow("Color Tracker", image)

			if cv2.waitKey(20) == 27:
				cv2.destroyWindow("Color Tracker")
				self.capture.release()
				self.running = False

class rover_proyect(object):
	def __init__(self):
		self.rotation = "l"
		self.search_goal = False
		self.point_x = None
		self.arr_dist = [6,1,2,3,8,2] 
		self.min_dist = 25.0
		
	def is_goal(self,f_goal):
		if (f_goal == True):
			self.search_goal == f_goal
			self.point_x = get_Xvalue()
		else:
			return self.rotation			
		
	def center_goal(self):
		if (self.point_x < 200):
			return "r"
		elif (self.point_x < 300):
			return "l"
		
	def move_goal(self):
		#for i in range(len(self.arr_dist)):
		if (self.arr_dist[2]<self.min_dist):
			return "r"
		elif (self.arr_dist[3]<self.min_dist):
			return "l"
		else:
			return "f"
				
			
	

if __name__=="__main__":
	color_tracker = ColorTracker()
	# search for blue
	color_tracker.set_color(np.array([110,50,50],np.uint8),np.array([130,255,255],np.uint8))
	print "Here"
	color_tracker.run()
	
		
	
