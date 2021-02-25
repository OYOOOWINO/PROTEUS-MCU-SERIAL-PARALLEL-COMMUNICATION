import serial
com = serial.Serial('COM5', 9600, timeout=.1)
while True:
	data = com.readline()[:-2]
	if data:
		print(data)