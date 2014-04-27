#!/usr/bin/env python

from color_tracker import *
from serial_comunication import *

class rover_project(object):
	def __init__(self):
		self.rotation = 'l'
		self.search_goal = False
		self.arr_dist = [100,200,300,400,500,600] 
		self.min_dist = 25.0
		self.mean = 3.0
		self.value_x = 250
		
	def is_goal(self,f_goal):
		if (f_goal == True):
			self.search_goal == f_goal
			self.point_x = get_Xvalue()
		else:
			return self.rotation			
				
	def center_goal(self,pos_num):
		if(pos_num <= 420 and pos_num >= 220 ):
			print "Center"
		elif(pos_num >= 300):
			print "move right"
			time.sleep(0.05)
			return "r"
			
		else:
			print "move left"
			time.sleep(0.05)
			return "l"
			
			
	def move_goal(self,array_dist):
	
		if (self.min_dist > array_dist[2]):
			print "Eluding obstacle to the right"
			self.rotation = 'l'
			time.sleep(0.05)
			return "r"
		elif (self.min_dist > array_dist[3]):
			print "Eluding obstacle to the left"
			self.rotation = 'r'
			time.sleep(0.05)
			return "l"			
		else:
			print "moving foward"
			time.sleep(0.05)
			return "f"
			
			
	
	def get_distances(self):
		self.write("R")
		
		
			
	def run(self):
		pass


def main():
	
		
	
	arduino_com = arduinoCom()	
	capture = ImageCapture("capture")
	blue_tracker = ColorTracker("blue_tracker")
	ro = rover_project()
	
	# search for blue color
	blue_tracker.set_color(np.array([110,50,50],np.uint8),np.array([130,255,255],np.uint8))
	display = ImageDisplay("display", title="Color Tracker")
	# connect elements
	blue_tracker.set_source(capture)
	display.set_source(blue_tracker)
	
	
	while True:
		
		capture.run()
		blue_tracker.run()
		pipeline = Pipeline()
		a =[200,200,200,200,200,200]
		
		
		#print "Here is the blue tracker", blue_tracker.get_x_center()
		arduino_com.write(ro.center_goal(blue_tracker.get_x_center()))
		arduino_com.write(ro.move_goal(a))
		#print arduino_com.arduino.readline()
		
		
		display.run()
		#pipeline.add_elements([capture, blue_tracker, display])
		#pipeline.link_elements()
		#pipeline.run()
		
		
		
	return 0

if __name__ == '__main__':
	main()

