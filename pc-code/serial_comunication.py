import serial
import time
import sys

class arduinoCom(object):
	def __init__(self):
		try:
			for device in range(0,5):
				self.arduino = serial.Serial("/dev/ttyACM%i" %device,9600)
				print("connected through /dev/ttyACM%i", device)
				break
		except:
			print("Can not connect to arduino device")
			sys.exit(-1)
	
	def write(self, message):
		 self.arduino.write(str(message))
	
def main():
	test = arduinoCom()
	test.write("f")
	time.sleep(1)
	test.write("r")
	time.sleep(1)
	test.write("l")
	time.sleep(1)
	return 0

if __name__ == '__main__':
	main()

