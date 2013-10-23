#!/usr/bin/env python

import glob
from time import sleep
import os
import RPi.GPIO as GPIO
from itertools import cycle

GPIO.setmode(GPIO.BCM)

class Button(object):
	def __init__(self, pin, directory, name=None):
		self._pin = pin
		self._directory = directory
		self._name = name

		if self._name is None:
			self._name = directory.split('/')[-1]


		GPIO.setup(self._pin, GPIO.IN)

		self._mp3s = sorted(glob.glob(directory+"/*mp3"))
		self._mp3_iter = cycle(self._mp3s)

		print "pin %d list %s" % (self._pin, repr(self._mp3s))

	def checkpin(self):
		res = GPIO.input(self._pin) 
		if ( res  == False):
			try:
				mp3 = self._mp3_iter.next()
				print("would play %s" % (mp3))
				os.system("mpg321 -q %s" % (mp3))
				
				while GPIO.input(self._pin) == False:
					sleep(0.1)

			except StopIteration:
				pass


button_array = []
button_array.append(Button(22,"/home/pi/ben-costume/buttons/next"))
button_array.append(Button(23,"/home/pi/ben-costume/buttons/destination"))
button_array.append(Button(24,"/home/pi/ben-costume/buttons/arrive"))
button_array.append(Button(25,"/home/pi/ben-costume/buttons/squeal"))
button_array.append(Button(8,"/home/pi/ben-costume/buttons/tracknoise"))
button_array.append(Button(18,"/home/pi/ben-costume/buttons/bell"))

#ding on startup`
os.system("mpg321 -q /home/pi/ben-costume/buttons/bell/bell.mp3")

while True:
	for button in button_array:
		button.checkpin()
	sleep(0.1);

