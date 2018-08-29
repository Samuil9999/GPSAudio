import RPi.GPIO as GPIO
import time
from threading import Timer

import pygame as pg

pg.mixer.init()
pg.init()

AUDIO_FOLDER = "/home/pi/Documents/Projects/GPSAudio/SoundMessages/wav_correct/"

sounds = []

# Append sound files to the list.
# The sound files were obtained using web cam microphone
# and internal Windows recording app. Then, https://online-audio-converter.com
# website had been used to batch convert all the *.wma into *.wav files with
# default settings.
print("Appending ... " + AUDIO_FOLDER + "warning.wav")
sounds.append(pg.mixer.Sound(AUDIO_FOLDER + "warning.wav"))
for i in range(1,21):
    print("Appending ... " + AUDIO_FOLDER + str(i) + ".wav")
    sounds.append(pg.mixer.Sound(AUDIO_FOLDER + str(i) + ".wav"))


INPUT0 = 16
INPUT1 = 20
INPUT2 = 21

def gpioCallback(channel):
	if(channel == INPUT0):
		global input0
		input0.processInterrupt()
	elif (channel == INPUT1):
		global input1
		input1.processInterrupt()
	elif (channel == INPUT2):
		global input2
		input2.processInterrupt()
		
class RInput:
	def __init__(self, number, pulselength):
		self.number = number
		self.pulselength = pulselength
		self.counter = 0
		self.lasttime = time.time()
		self.delta = 0
		self.initTimer()
		GPIO.setmode(GPIO.BCM)
		GPIO.setup(number, GPIO.IN, pull_up_down=GPIO.PUD_UP)
		#GPIO.setup(number, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
		#GPIO.setup(number, GPIO.IN)
		GPIO.add_event_detect(number, GPIO.BOTH, callback=gpioCallback, bouncetime=100)
		print("RInput:" + str(number) + " created.")
	
	def processInterrupt(self):
		self.delta = time.time() - self.lasttime
		# if this is a start of pulse, then increment
		if GPIO.input(self.number) == False:
			self.counter += 1
			print("time.time() - lasttime:%s, counter:%s" % \
				(time.time() - self.lasttime, self.counter))
		elif GPIO.input(self.number) == True:
			self.timer.cancel()
			self.initTimer()
			self.timer.start()

	def initTimer(self):
		self.timer = Timer(self.pulselength + 0.1, self.playAudio)

	def playAudio(self):
		if(self.number == INPUT0):
			print("Warning!!!")
			sound = sounds[0]
			sound.play()
			##for sound in sounds:
			##    sound.play()
		elif(self.number == INPUT1):
			if self.counter >=1 and self.counter <=15:
				print("Playing audio number " + str(self.counter))
				sound = sounds[self.counter]
				sound.play()
			else:
				print("Cannot play audio number " + str(self.counter) + ". Out of range.")
		elif(self.number == INPUT2):
			if self.counter >=1 and self.counter <=15:
				print("Playing audio number " + str(self.counter + 15) + " at INPUT1")
				sound = sounds[self.counter + 15]
				sound.play()
			else:
				print("Cannot play audio number " + str(self.counter + 15) \
				 + ". Pulse number (" + str(self.counter) + ") at INPUT2 " \
				 + " is out of range.")
		self.counter = 0
	
input0 = RInput(INPUT0, 2.5);
input1 = RInput(INPUT1, 2.5);
input2 = RInput(INPUT2, 2.5);

while True:
	time.sleep(1)
