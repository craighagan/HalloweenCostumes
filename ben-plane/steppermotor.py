#!/usr/bin/env python
#
# wrapper for my 28BYJ-48 with a ULN2003
# board
#
# the basics stolen from :
# http://www.raspberrypi-spy.co.uk/2012/07/stepper-motor-control-in-python/

import time
import RPi.GPIO as GPIO

# cleanup anything which may already have been
# programmed
GPIO.cleanup()

# Use BCM GPIO references
# instead of physical pin numbers
GPIO.setmode(GPIO.BCM)


class StepperMotor(object):
    def __init__(self, pins, wait_time=0.0001, speed=0.0001):
        """
        @pins : array of input pins, e.g. [5,6,13,19]
        @wait_time : delay between step execution, defaults to 0.0001
        @speed : higher = slower, slow is 0.001, best tested is 0.00006
        """
        self._pins = pins
        self.speed = speed
        self.wait_time = wait_time
        self.iterations_per_revolution = 510
        self.clockwise_steps = [
            [1, 0, 0, 0],
            [1, 1, 0, 0],
            [0, 1, 0, 0],
            [0, 1, 1, 0],
            [0, 0, 1, 0],
            [0, 0, 0, 1],
            [1, 0, 0, 1],
        ]

        self.poweroff_steps = [
            [0, 0, 0, 0],
        ]

        # validation
        for step in self.clockwise_steps:
            assert(len(step) == len(self._pins))

        # setup the pins
        for pin in self._pins:
            GPIO.setup(pin, GPIO.OUT)

    def _execute_steps(self, steps):
        for step in steps:
            for pin in xrange(len(self._pins)):
                if step[pin] != 0:
                    GPIO.output(self._pins[pin], True)
                else:
                    GPIO.output(self._pins[pin], False)
                time.sleep(self.speed)

    def poweroff(self):
        self._execute_steps(self.poweroff_steps)

    def rotate_clockwise(self, iterations, poweroff=True):
        """
        @iterations : how many repeats of the steps to run,
        510 iterations is about 360 degrees
        """
        for i in xrange(int(iterations)):
            self._execute_steps(self.clockwise_steps)
            # Wait before moving on
            time.sleep(self.wait_time)

        if poweroff:
            self.poweroff()

    def rotate_counterclockwise(self, iterations, poweroff=True):
        """
        @iterations : how many repeats of the steps to run,
        510 iterations is about 360 degrees
        """
        for i in xrange(int(iterations)):
            self._execute_steps(reversed(self.clockwise_steps))
            # Wait before moving on
            self.poweroff()
            time.sleep(self.wait_time)

        if poweroff:
            self.poweroff()

    def clockwise(self, revolutions=1):
        """
        @revolutions roughly how many revolutions to rotate
        """
        self.rotate_clockwise(revolutions * self.iterations_per_revolution, poweroff=False)
        self._execute_steps(self.poweroff_steps)

    def counterclockwise(self, revolutions=1):
        """
        @revolutions roughly how many revolutions to rotate
        """
        self.rotate_counterclockwise(revolutions * self.iterations_per_revolution, poweroff=False)
        self.poweroff()
