#!/usr/bin/env python
import smbus
import time
 
bus = smbus.SMBus(1)
address = 0x09
GenCount=0
#def write(value):
#        bus.write_byte_data(address, 0, value)
#        return -1
        
while (1):
  #  write(0x10)
  time.sleep(1)
  #LBS = bus.read_byte_data(address,10)
  data = bus.read_i2c_block_data(0x09, 0x10, 8)
  data1 = (data[0]<<24) + (data[1]<<16) + (data[2]<<8) + data[3]
  data2 = (data[4]<<24) + (data[5]<<16) + (data[6]<<8) + data[7]
  print GenCount, "\t", data1, "\t", data2
  GenCount=GenCount+1
  #print LBS
   
    
    
bus.close()
#  time.sleep(1)

