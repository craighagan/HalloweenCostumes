#!/usr/bin/env python

import glob
from time import sleep, time
import os
from itertools import cycle
import threading
import subprocess
import RPi.GPIO as GPIO
import steppermotor

last_played_time = time() + 3600
sound_interval = 2 * 60
gain = 90

GPIO.cleanup()
GPIO.setmode(GPIO.BCM)


class RunWheels(threading.Thread):

    def __init__(self, group=None,
                 target=None,
                 name=None,
                 verbose=None,
                 pins=[],
                 speed=0.0006,
                 clockwise=True):
        threading.Thread.__init__(self,
                                  group=group,
                                  target=target,
                                  name=name,
                                  verbose=verbose)
        self._stop = threading.Event()
        self.StepperMotor = steppermotor.StepperMotor(pins, speed=speed)
        self.clockwise = clockwise

    def stop(self):
        self._stop.set()

    def run(self):
        while not self._stop.is_set():
            if self.clockwise:
                self.StepperMotor.rotate_clockwise(100)
            else:
                self.StepperMotor.rotate_counterclockwise(100)
            sleep(0.05)


class MarkerLights(threading.Thread):
    def __init__(self, left, right, tail,
                 group=None,
                 target=None,
                 name=None,
                 verbose=None):
        self.left = left
        self.right = right
        self.tail = tail


        GPIO.setup(self.left, GPIO.OUT)
        GPIO.setup(self.right, GPIO.OUT)
        GPIO.setup(self.tail, GPIO.OUT)

        threading.Thread.__init__(self,
                                  group=group,
                                  target=target,
                                  name=name,
                                  verbose=verbose)
        self._stop = threading.Event()

    def _short_blink(self, pin):
        GPIO.output(pin, GPIO.HIGH)
        sleep(0.1)
        GPIO.output(pin, GPIO.LOW)
        sleep(0.2)
        GPIO.output(pin, GPIO.HIGH)
        sleep(0.1)
        GPIO.output(pin, GPIO.LOW)

    def stop(self):
        self._stop.set()

    def run(self):
        while not self._stop.is_set():
            self._short_blink(self.left)
            self._short_blink(self.right)
            self._short_blink(self.tail)
            sleep(0.05)


class Button(object):
    def __init__(self, pin, directory, name=None,
                 stop_if_depress=False):
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
            prop = RunWheels(pins=[27, 17, 23, 24], name="Prop")
            mp3 = self._mp3_iter.next()
            print("would play %s" % (mp3))
            #os.system("mpg321 -q %s -g %s" % (mp3, gain))
            cmd = ["mpg321", "-g", str(gain), "-q", mp3, ]
            p = subprocess.Popen(cmd)

            if not self._stop_if_depress:
                prop.start()
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

            prop.stop()

        except StopIteration:
            pass

    def checkpin(self):
        res = GPIO.input(self._pin)

        if (res == False):
            self.play_sound()



# initialize sound
os.system("sudo amixer cset numid=0")
#os.system("sudo amixer set PCM -- -2800")
os.system("sudo amixer set PCM -- 00")
os.system("sudo alsactl store")

# ding on startup`
prop = RunWheels(pins=[27, 17, 23, 24], name="Prop")
marker_lights = MarkerLights(5, 6, 16)

button_array = []
button_array.append(Button(26, "/home/pi/ben-plane/buttons/sounds"))

marker_lights.start()
prop.start()
os.system("mpg321 -q /home/pi/ben-plane/buttons/sounds/p51-start.mp3")
prop.stop()
last_played_time = time()
last_played_button = 0

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
