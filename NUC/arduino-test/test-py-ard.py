import time
import serial
import pyfirmata


board = pyfirmata.Arduino('/dev/ttyACM0')
ser =  serial.Serial('/dev/ttyACM0')
print(ser.name)
i=0
#ser.open()
while True:
	#ser.write(b'holis\r\n')#escribe en el puerto serial
	time.sleep(3)
	#ser.flush()
	#print("pasa flush")
	x = ser.readline()
	print(x.decode("latin-1") )
	
	#print(x)
	ser.close()#cierra el puerto serial, es necesario hacerlo despues de cualquier actividad con el puerto serial
	i+=1
	## lectura de puerto analogo (puede aplicarse a digital)
	""""
	if board.analog[0].read()==None:
		pass
	else:
		print(board.analog[0])
	"""
	#ser.open()
	#ser.close()
	#print("encendido")
	#board.digital[13].write(1)#enciende el pin 13
	#time.sleep(0.1)
	#print("apagada")
	#board.digital[13].write(0)
	#time.sleep(0.1)
	ser.open()
	
