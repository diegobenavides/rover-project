
#serial communication 1


import serial
import time
import sys


class arduinoCom(object):
	def __init__(self):
		try:
			self.arduino = serial.Serial("/dev/ttyACM0" ,9600,timeout=2)
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
		print "here start to send q"
		test.write("w")
		
		print test.readline_A()
		time.sleep(0.005)
		
		
		 
		
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





"""
import serial


#Serial communication 2

#!/usr/bin/env python

import serial

class Arduino(object):

    __OUTPUT_PINS = -1

    def __init__(self, port, baudrate=115200):
        self.serial = serial.Serial(port, baudrate)
        self.serial.write('99')

    def __str__(self):
        return "Arduino is on port %s at %d baudrate" %(self.serial.port, self.serial.baudrate)

    def output(self, pinArray):
        self.__sendData(len(pinArray))

        if(isinstance(pinArray, list) or isinstance(pinArray, tuple)):
            self.__OUTPUT_PINS = pinArray
            for each_pin in pinArray:
                self.__sendData(each_pin)
        return True

    def setLow(self, pin):
        self.__sendData('0')
        self.__sendData(pin)
        return True

    def setHigh(self, pin):
        self.__sendData('1')
        self.__sendData(pin)
        return True

    def getState(self, pin):
        self.__sendData('2')
        self.__sendData(pin)
        return self.__formatPinState(self.__getData()[0])

    def analogWrite(self, pin, value):
        self.__sendData('3')
        self.__sendData(pin)
        self.__sendData(value)
        return True

    def analogRead(self, pin):
        self.__sendData('4')
        self.__sendData(pin)
        return self.__getData()

    def turnOff(self):
        for each_pin in self.__OUTPUT_PINS:
            self.setLow(each_pin)
        return True

    def __sendData(self, serial_data):
        while(self.__getData()[0] != "w"):
            pass
        self.serial.write(str(serial_data))

    def __getData(self):
        return self.serial.readline().rstrip('\n')

    def __formatPinState(self, pinValue):
        if pinValue == '1':
            return True
        else:
            return False

    def close(self):
        self.serial.close()
        return True


def main():
	ard = Arduino("/dev/ttyACM0" ,9600)
	
	ard.__getData()
	
	
	return 0
	
if __name__ == '__main__':
	main()



"""
