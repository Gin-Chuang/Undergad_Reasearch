import picamera
import serial
import time
import os

from collections import deque
from datetime import datetime

directory = str(datetime.now().date())
parent_dir = f'/home/pi/Desktop/Gin/'

path = os.path.join(parent_dir, directory)

if not os.path.exists(path):
    os.mkdir(path)
    print("Directory", directory, "created")
else:
    print("Directory", directory, "already exists")    

resolution = 1440, 1080
# higher !
camera = picamera.PiCamera(resolution=resolution)
camera.start_preview()

with serial.Serial('/dev/ttyACM0', 9600) as arduino:
    print(arduino.name)
    
    data = deque(maxlen=8)
    start = time.perf_counter()
    while time.perf_counter() - start < 10:
        ## set photo total time
        try:
            data.append(arduino.read().decode())
        except serial.serialutil.SerialException:
            continue
        
        if len(data) > 1 and data[-2] == 'p':
            x, y, z = [], [], []
            for i in data:
                if i == 'x':
                    a = x
                elif i == 'y':
                    a = y
                elif i == 'p':
                    a = z
                else:
                    try:
                        a.append(i)
                    except NameError:
                        break
            
            if len(x) != 2 or len(y) != 2 or len(z) != 1:
                continue
            
            print(data)
            x = int(''.join(x))
            y = int(''.join(y))
            if z[0]:
                camera.capture(f'/home/pi/Desktop/Gin/{datetime.now().date()}/{x}_{y}_{datetime.now().date()}.jpg')

camera.stop_preview()
camera.close()
