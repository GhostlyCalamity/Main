#!/usr/bin/env python
import smbus
import time

bus = smbus.SMBus(1)
address = 0x09
GenCount=0

while True:
	data1 = bus.read_byte(address)
	data2 = bus.read_byte(address)
	data3 = bus.read_byte(address)
	data4 = bus.read_byte(address)
	data = (data1<<24) + (data2<<16) + (data3<<8) + data4

	print GenCount, "\t", hex(data), "\t", data
	GenCount=GenCount+1
	time.sleep(1)

bus_close()