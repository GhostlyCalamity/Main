import smbus
import time
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import style
 
bus = smbus.SMBus(1)
address = 0x09
GenCount=0

style.use('fivethirtyeight')
fig = plt.figure()
ax1 = fig.add_subplot(1,1,1)

while (1):
    time.sleep(1)
    data = bus.read_i2c_block_data(0x09, 0x10, 8)
    data1 = (data[0]<<24) + (data[1]<<16) + (data[2]<<8) + data[3]
    data2 = (data[4]<<24) + (data[5]<<16) + (data[6]<<8) + data[7]
    f = open('realtime', 'at')
    f.write(str(GenCount)+'\t'+str(data1)+'\t'+str(data2)+'\n')
    f.close()
   # graph_data = open('realtime','r').read()
    #    lines = graph_data.split('\n')
     #   xs = []
      #  ys = []
       # zs = []
        #for line in lines:
         #   if len(line) > 1:
          #      x, y, z= line.split('\t')
           #     xs.append(float(x))
            #    ys.append(float(y))
             #   zs.append(float(z))
        #ax1.clear()
        #ax1.plot(xs, ys)
    lines = plt.plot(GenCount, data1, 'r^', GenCount, data2, 'go')
    #plt.setp(lines, color='r', linewidth=2.0)
    #lines2 = plt.scatter(GenCount, data2)
    #plt.setp(lines2, color='g',linewidtg=3.0)
    plt.pause(0.05)
    GenCount=GenCount+1
    #ani = animation.FuncAnimation(fig, animate, interval=100)
plt.show()
#plt.draw()
    #print (GenCount, "\t", data1, "\t", data2)
    
  
bus.close()


