"""
Created on 2021/10/19
Lacewing_Camera
@author: Jim
"""
import os
import time
from datetime import datetime
receivetime = time.strftime('%m%d_%H%M',time.localtime(time.time()))
if os.path.exists("/home/pi/Desktop/lacewing") == False: os.mkdir("/home/pi/Desktop/lacewing")
os.system('raspistill -br 60 -o /home/pi/Desktop/lacewing/'+receivetime+'.jpg -t 3000')
print('photo taken')
