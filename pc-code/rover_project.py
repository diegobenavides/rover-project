from color_tracker import *
from serial_comunication import *


class rover_project(object):
	
	def __init__(self):
		self.rotation = 'l'
		self.search_the_goal = False
		self.arr_dist = [200,200,200,200,200,200] 
		self.arr_str = ['q','w','t','y','u','i'] 
		self.min_dist = 25.0
		self.mean = 3.0
		self.value_x = 250
		self.delay = 0.01
		self.rover_active = False		
		self.pos ='q' 
		self.direct = 1 
				
	def get_arr_dis(self):
		return self.arr_str
	
	def set_activation(self,active):
		self.rover_active = active
		
	def get_activation(self):
		return self.rover_active
		
	def is_goal(self,f_goal):
		if (f_goal == True):
			self.search_goal == f_goal
			self.point_x = get_Xvalue()
		else:
			return self.rotation			
			
	def search_goal(self):
		return "l"
	
	def center_goal(self,pos_num):
		if(pos_num <= 420 and pos_num >= 220 ):
			print "Center"
		elif(pos_num >= 300):
			print "move right"
			time.sleep(self.delay)
			return "r"
			
		else:
			print "move left"
			time.sleep(self.delay)
			return "l"
	
	def get_meanX(self, n_sample): 
		if (n_sample != None):
			self.mean = (self.mean + n_sample)/2
			return self.mean 
			
			
	def move_goal(self,array_dist):
	
		if (self.min_dist > array_dist[2]):
			print "Eluding obstacle to the right"
			self.rotation = 'l'
			time.sleep(self.delay)
			return "r"
		elif (self.min_dist > array_dist[3]):
			print "Eluding obstacle to the left"
			self.rotation = 'r'
			time.sleep(self.delay)
			return "l"			
		else:
			print "moving foward"
			time.sleep(self.delay)
			return "f"
			
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
	ro.set_activation(True)
	
	while (ro.get_activation()):

		
		capture.run()
		blue_tracker.run()
		pipeline = Pipeline()
		
		print ro.get_meanX(blue_tracker.get_x_center())
		
		#print "Here is the blue tracker", blue_tracker.get_x_center()
		arduino_com.write(ro.center_goal(blue_tracker.get_x_center()))
		
		arduino_com.write(ro.move_goal(ro.get_arr_dis()))
		
		#time.sleep(0.005)
		
		display.run()
		#pipeline.add_elements([capture, blue_tracker, display])
		#pipeline.link_elements()
		#pipeline.run()
		
		
		
		
	return 0

if __name__ == '__main__':
	main()


