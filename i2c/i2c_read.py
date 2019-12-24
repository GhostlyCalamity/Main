#!/usr/bin/env python
import smbus
import time
 
bus = smbus.SMBus(1)
address = 0x09

#def write(value):
#        bus.write_byte_data(address, 0, value)
#        return -1
        
while (1):
  #  write(0x10)
  time.sleep(1)
  #LBS = bus.read_byte_data(address,10)
  data = bus.read_i2c_block_data(0x09, 0x10, 4)
  data1 = (data[0]<<24) + (data[1]<<16) + (data[2]<<8) + data[3]
  print data1
  #print LBS
   
    
    
bus.close()
#  time.sleep(1)

