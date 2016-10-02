#!/usr/bin/python


import os
import json
import sys

DEFAULT_GAIN = 90

def _get_gain(mp3):
    play_gain = DEFAULT_GAIN
    mp3_config = mp3 + '.json'
    print "config is %s" % mp3_config
    if os.path.exists(mp3_config):
        mp3_config = json.load(file(mp3_config))
        config_gain = mp3_config.get('gain')
        if config_gain:
            play_gain = config_gain
    print "gain is %s" % play_gain
    return play_gain


mp3 = sys.argv[1]
os.system("mpg321 -q -g %s %s " % (_get_gain(mp3), mp3))
