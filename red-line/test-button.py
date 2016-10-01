#!/usr/bin/env python

import glob
from time import sleep, time
import os
from itertools import cycle
import threading
import subprocess
import RPi.GPIO as GPIO

last_played_time = time() + 3600
sound_interval = 2 * 60
gain = 250

GPIO.cleanup()
GPIO.setmode(GPIO.BCM)


class Button(object):

    def __init__(self, pin, directory, name=None, stop_if_depress=False):
        self._pin = pin
        self._directory = directory
        self._name = name
        self._stop_if_depress = stop_if_depress

        if self._name is None:
            self._name = directory.split('/')[-1]

        GPIO.setup(self._pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)

        self._mp3s = sorted(glob.glob(directory + "/*mp3"))
        self._mp3_iter = cycle(self._mp3s)

        print "pin %d list %s" % (self._pin, repr(self._mp3s))

    def play_sound(self):
        global last_played_time

        try:
            mp3 = self._mp3_iter.next()
            print("would play %s" % (mp3))
            #os.system("mpg321 -q %s -g %s" % (mp3, gain))
            cmd = ["mpg321", "-g", str(gain), "-q",  mp3, ]
            p = subprocess.Popen(cmd)

            if not self._stop_if_depress:
                p.communicate()

            else:  # music time
                while p.poll() is None:
                    if GPIO.input(self._pin):
                        p.kill()
                    else:
                        sleep(0.1)

            while GPIO.input(self._pin) == False:
                sleep(0.1)

            last_played_time = time()
            print "set last_played_time to %s" % last_played_time

        except StopIteration:
            pass

    def checkpin(self):
        res = GPIO.input(self._pin)

        if (res == False):
            self.play_sound()


button_array = []
button_array.append(Button(22, "/home/pi/red-line/buttons/door"))
button_array.append(Button(23, "/home/pi/red-line/buttons/next-stop"))
button_array.append(Button(24, "/home/pi/red-line/buttons/now-arriving"))
button_array.append(Button(24, "/home/pi/red-line/buttons/now-arriving"))

# initialize sound
os.system("sudo amixer cset numid=0")
#os.system("sudo amixer set PCM -- -2800")
os.system("sudo amixer set PCM -- 00")
os.system("sudo alsactl store")

# ding on startup`

os.system("mpg321 -q -g %s /home/pi/red-line/buttons/door/redline-door-beep.mp3" % gain)
last_played_time = time()
last_played_button = 0

try:
    while True:
        for button in button_array:
            button.checkpin()

        if (last_played_time + sound_interval) < time():
            print "last played is %s curtime is %s" % (last_played_time + sound_interval, time())
            button_array[last_played_button].play_sound()
            last_played_button += 1

            if last_played_button >= len(button_array):
                last_played_button = 0

        sleep(0.1)
except:
    raise

finally:
    GPIO.cleanup()