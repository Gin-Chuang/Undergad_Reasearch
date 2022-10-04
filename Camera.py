from picamera import Picamera
from time import sleep

camera = PiCamera()

camera.start_preview()
for i in range(3):
    sleep(5)
    camera.capture(r'/home/pi/Desktop/image31_%.jpg' % i)
camera.stop_preview()