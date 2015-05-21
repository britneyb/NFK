import serial
import re
import sqlite3

ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1) # Establish the connection on a specific port

con = sqlite3.connect('sqltemptime.db')
c = con.cursor();

while ser.isOpen():
	data = (ser.readline()).decode('utf-8')
	if data != "":
		match = re.match(r'\w+,\d+,\d+,\d+,\d+', data)
		#print(match)
		if match:
			match2 = re.search(r'(\w+),(\d+),(\d+),(\d+),(\d+)', match.group(0))
			print(match2.group(4)+":"+match2.group(5)+":"+match2.group(2)+":"+match2.group(3))
			_time = match2.group(4)
			_temp = match2.group(5)
			_id = match2.group(2)
			if match2.group(1) == "boil":
				_time = int(match2.group(3))-int(_time)
			
			c.execute("INSERT INTO timeTemp (time, temp, id) VALUES (?, ?, ?)", ("{}".format(_time), "{}".format(_temp), "{}".format(_id)))
			con.commit()
			print(match2.group(1)+":"+match2.group(2)+":"+match2.group(3)+":"+match2.group(4))

