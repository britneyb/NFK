from time import sleep
import serial
import time
import socket
import os


gw = os.popen("ip -4 route show default").read().split()
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.connect((gw[2], 0))
ipaddr = s.getsockname()[0]

print ("IP:", ipaddr)





ser = serial.Serial('/dev/ttyACM0', 9600) # Establish the connection on a specific port


ser.write("ip,"+ipaddr)




