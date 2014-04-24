#!/usr/bin/env python

class rover_project(object):
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


def main():
	
	return 0

if __name__ == '__main__':
	main()

