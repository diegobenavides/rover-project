import serial
import time  

def main():
	try:  
		arduino = serial.Serial('/dev/ttyACM0', 9600)  
	except:
		print "Failed to connect on /dev/ttyACM0"
		
	while(True):
		arduino.write('f')
		time.sleep(1)
		print arduino.readline()
		
	return 0
	
	

if __name__ == '__main__':
	main()

