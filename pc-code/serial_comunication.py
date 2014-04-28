import serial
import time
import sys


class arduinoCom(object):
	def __init__(self):
		try:
			self.arduino = serial.Serial("/dev/ttyACM0" ,9600)
			print("Connected to Arduino")	
		except:
			print("Can not connect to arduino device")
			sys.exit(-1)
		#time.sleep(0.5)
			
	def write(self, message):
		 self.arduino.write(str(message))
		 
	def readline_A(self):
		 return self.arduino.readline()
	
	
def main():
	
	test = arduinoCom()
	
	
	while True:
		test.write("q")
		print test.arduino.readline()
		print "HEre"
		
		 
		
	"""
	while True:
		test.write("q")
		a = test.arduino.readline()
		print "data",a
		 

	print "Here"
	while True:
		print test.readline_A()
	
	#print "Here ",test.arduino.readline()
	print "Reading... ",test.arduino.readline()
	#test.write("R")
		
	print "Here ",test.arduino.readline()
	print "Reading... ",test.arduino.readline()
	test.write("R")
	print "1",test.arduino.readline()
	print "2",test.arduino.readline()
	print "3",test.arduino.readline()
	print "4",test.arduino.readline()
	print "5",test.arduino.readline()
		
	
	test.write("r")
	time.sleep(1)
	test.write("b")
	time.sleep(1)
	"""
	return 0
	
if __name__ == '__main__':
	main()

