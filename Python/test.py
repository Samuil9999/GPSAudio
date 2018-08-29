import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

first_counter = 0

def first_input_callback(channel):
    #print('You pressed the button' + str(channel))
    first_counter += 1

GPIO.setup(16, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.add_event_detect(16, GPIO.FALLING, callback=first_input_callback) 

while True:
    print(first_counter)
    time.sleep(1)
    
