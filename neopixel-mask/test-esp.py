
try:
    import machine
    import neopixel
    esp = True
except ImportError:
    esp = False
    import mock


class FakeNeoPixel(object):
    def __init__(self, nr_leds):
        self.nr_leds = nr_leds
        self.data = {}

    def __setitem__(self, index, value):
        assert index >= 0, 'index %d must be > 0' % index
        assert index < self.nr_leds, 'index %d must be less than %d' % (index, self.nr_leds)
        self.data[index] = value

    def __getitem__(self, index):
        try:
            return self.data[index]
        except KeyError:
            return (0, 0, 0)

    def write(self):
        pass


import time

MESSAGES = [
    "     COVID SUCKS!",
    "     HAPPY HALLOWEEN! ",
]
MAX_PIXELS = 8 * 32
IO_PIN = 14

if esp:
    np = neopixel.NeoPixel(machine.Pin(IO_PIN), MAX_PIXELS)
else:
    np = FakeNeoPixel(MAX_PIXELS)


def clear():
    for i in range(MAX_PIXELS):
        np[i] = (0, 0, 0)
    np.write()


def on():
    for i in range(MAX_PIXELS):
        np[i] = (255, 255, 255)
    np.write()


def cycle(r, g, b, wait=50):
    for i in range(4 * MAX_PIXELS):
        for j in range(MAX_PIXELS):
            np[j] = (0, 0, 0)
        np[i % MAX_PIXELS] = (r, g, b)
        np.write()
        time.sleep_ms(wait)


chars = {
    '1': [[0, 1, 0, 0, 0, 0, 0, 1],
          [1, 1, 1, 1, 1, 1, 1, 1],
          [0, 0, 0, 0, 0, 0, 0, 1]],
    '!': [[0, 0, 0, 0, 0, 0, 0, 0],
          [1, 1, 1, 1, 1, 0, 1, 0],
          [0, 0, 0, 0, 0, 0, 0, 0]],
    ' ': [[0, 0, 0, 0, 0, 0, 0, 0],
          [0, 0, 0, 0, 0, 0, 0, 0],
          [0, 0, 0, 0, 0, 0, 0, 0],
          [0, 0, 0, 0, 0, 0, 0, 0],
          [0, 0, 0, 0, 0, 0, 0, 0]],

    'A': [[0, 1, 1, 1, 1, 1, 1, 0],
          [1, 0, 0, 1, 0, 0, 0, 0],
          [1, 0, 0, 1, 0, 0, 0, 0],
          [1, 0, 0, 1, 0, 0, 0, 0],
          [0, 1, 1, 1, 1, 1, 1, 0]],

    'B': [[1, 1, 1, 1, 1, 1, 1, 0],
          [1, 0, 0, 1, 0, 0, 1, 0],
          [1, 0, 0, 1, 0, 0, 1, 0],
          [1, 0, 0, 1, 0, 0, 1, 0],
          [0, 1, 1, 0, 1, 1, 0, 0]],

    'C': [[0, 1, 1, 1, 1, 1, 0, 0],
          [1, 0, 0, 0, 0, 0, 1, 0],
          [1, 0, 0, 0, 0, 0, 1, 0],
          [1, 0, 0, 0, 0, 0, 1, 0],
          [0, 1, 0, 0, 0, 1, 0, 0]],

    'D': [[1, 1, 1, 1, 1, 1, 1, 0],
          [1, 0, 0, 0, 0, 0, 1, 0],
          [1, 0, 0, 0, 0, 0, 1, 0],
          [1, 0, 0, 0, 0, 0, 1, 0],
          [0, 1, 1, 1, 1, 1, 0, 0]],

    'E': [[1, 1, 1, 1, 1, 1, 1, 0],
          [1, 0, 0, 1, 0, 0, 1, 0],
          [1, 0, 0, 1, 0, 0, 1, 0],
          [1, 0, 0, 1, 0, 0, 1, 0],
          [1, 0, 0, 1, 0, 0, 1, 0]],

    'H': [[1, 1, 1, 1, 1, 1, 1, 0],
          [0, 0, 0, 1, 0, 0, 0, 0],
          [0, 0, 0, 1, 0, 0, 0, 0],
          [0, 0, 0, 1, 0, 0, 0, 0],
          [1, 1, 1, 1, 1, 1, 1, 0]],

    'I': [[1, 0, 0, 0, 0, 0, 1, 0],
          [1, 0, 0, 0, 0, 0, 1, 0],
          [1, 1, 1, 1, 1, 1, 1, 0],
          [1, 0, 0, 0, 0, 0, 1, 0],
          [1, 0, 0, 0, 0, 0, 1, 0]],

    'K': [[1, 1, 1, 1, 1, 1, 1, 0],
          [0, 0, 0, 1, 0, 0, 0, 0],
          [0, 0, 1, 0, 1, 0, 0, 0],
          [0, 1, 0, 0, 0, 1, 0, 0],
          [1, 0, 0, 0, 0, 0, 1, 0]],

    'L': [[1, 1, 1, 1, 1, 1, 1, 0],
          [0, 0, 0, 0, 0, 0, 1, 0],
          [0, 0, 0, 0, 0, 0, 1, 0],
          [0, 0, 0, 0, 0, 0, 1, 0],
          [0, 0, 0, 0, 0, 0, 1, 0]],

    'N': [[1, 1, 1, 1, 1, 1, 1, 0],
          [0, 1, 1, 0, 0, 0, 0, 0],
          [0, 0, 0, 1, 1, 0, 0, 0],
          [0, 0, 0, 0, 0, 1, 0, 0],
          [1, 1, 1, 1, 1, 1, 1, 0]],

    'O': [[0, 1, 1, 1, 1, 1, 0, 0],
          [1, 0, 0, 0, 0, 0, 1, 0],
          [1, 0, 0, 0, 0, 0, 1, 0],
          [1, 0, 0, 0, 0, 0, 1, 0],
          [0, 1, 1, 1, 1, 1, 0, 0]],

    'P': [[1, 1, 1, 1, 1, 1, 1, 0],
          [1, 0, 0, 1, 0, 0, 0, 0],
          [1, 0, 0, 1, 0, 0, 0, 0],
          [1, 0, 0, 1, 0, 0, 0, 0],
          [1, 1, 1, 1, 0, 0, 0, 0]],

    'S': [[0, 1, 1, 0, 0, 0, 0, 0],
          [1, 0, 0, 1, 0, 0, 1, 0],
          [1, 0, 0, 1, 0, 0, 1, 0],
          [1, 0, 0, 1, 0, 0, 1, 0],
          [0, 0, 0, 0, 1, 1, 0, 0]],

    'T': [[1, 0, 0, 0, 0, 0, 0, 0],
          [1, 0, 0, 0, 0, 0, 0, 0],
          [1, 1, 1, 1, 1, 1, 1, 0],
          [1, 0, 0, 0, 0, 0, 0, 0],
          [1, 0, 0, 0, 0, 0, 0, 0]],

    'U': [[1, 1, 1, 1, 1, 1, 0, 0],
          [0, 0, 0, 0, 0, 0, 1, 0],
          [0, 0, 0, 0, 0, 0, 1, 0],
          [0, 0, 0, 0, 0, 0, 1, 0],
          [1, 1, 1, 1, 1, 1, 0, 0]],

    'V': [[1, 1, 1, 1, 0, 0, 0, 0],
          [0, 0, 0, 0, 1, 1, 0, 0],
          [0, 0, 0, 0, 0, 0, 1, 0],
          [0, 0, 0, 0, 1, 1, 0, 0],
          [1, 1, 1, 1, 0, 0, 0, 0]],

    'W': [[1, 1, 1, 1, 1, 1, 0, 0],
          [0, 0, 0, 0, 0, 0, 1, 0],
          [1, 1, 1, 1, 1, 1, 1, 0],
          [0, 0, 0, 0, 0, 0, 1, 0],
          [1, 1, 1, 1, 1, 1, 0, 0]],

    'Y': [[1, 1, 1, 0, 0, 0, 0, 0],
          [0, 0, 0, 1, 0, 0, 0, 0],
          [0, 0, 0, 0, 1, 1, 1, 0],
          [0, 0, 0, 1, 0, 0, 0, 0],
          [1, 1, 1, 0, 0, 0, 0, 0]],
}


def show_character(color, char, np, offset=0, write=False):
    data = chars[char]

    pos = 0 + offset
    for line in data:
        subpos = 0
        if pos % 2:
            line = reversed(line)
        for c in line:
            pixel = 8 * pos + subpos
            if pixel < MAX_PIXELS:
                if c:
                    np[pixel] = color
                else:
                    np[pixel] = (0, 0, 0)
                subpos += 1

                #print("set pixel %d to %s" % (pixel, np[pixel]))

        pos += 1

    if write:
        np.write()


def draw_line(str, color, np, width=6):
    nr = 0
    for char in str[0:5]:
        show_character(color, char, np, offset=width * nr)
        nr += 1
    np.write()


def draw_pos(cur_pos, message, msg_len):
    clear()
    debug = ""
    line_pos = 0
    for x in range(cur_pos, cur_pos + min(msg_len - cur_pos, 5)):
        char = message[x]
        debug += char
        line_pos += 1
    print("[%s]" % debug)
    draw_line(debug, color, np)


while True:
    for message in MESSAGES:
        msg_len = len(message)
        cur_pos = 0
        width = 6
        color = (255, 25, 0)

        while cur_pos < msg_len:
            draw_pos(cur_pos, message, msg_len)
            cur_pos += 1
            time.sleep(0.15)
    time.sleep(0.15)
