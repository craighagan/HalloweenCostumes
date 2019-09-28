// Low power NeoPixel earrings example.  Makes a nice blinky display
// with just a few LEDs on at any time...uses MUCH less juice than
// rainbow display!

#include <Adafruit_NeoPixel.h>

#define PIN       0
#define NUM_LEDS 60
#define MAX_MODES 10
#define DEFAULT_COLOR 0x0000FF

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, PIN);

uint8_t  mode   = 0,              // Current animation effect
         offset = 0;              // Position of spinner animation
uint32_t color  = DEFAULT_COLOR;  // Starting color = amber
uint32_t prevTime;                // Time of last animation mode switch



// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void setup() {
  pixels.begin();
  pixels.setBrightness(25); // ~1/3 brightness
  prevTime = millis();      // Starting time
}

void loop() {
  uint8_t  i;
  uint8_t  j;
  uint32_t t;
  uint32_t randcolor = 0;
  uint8_t nr_colors = 0;

  switch (mode) {

    case 0: // Random sparkles - just one LED on at a time!
      i = random(NUM_LEDS);           // Choose a random pixel
      pixels.setPixelColor(i, color); // Set it to current color
      pixels.show();                  // Refresh LED states
      // Set same pixel to "off" color now but DON'T refresh...
      // it stays on for now...both this and the next random
      // pixel will be refreshed on the next pass.
      pixels.setPixelColor(i, 0);
      delay(10);                      // 10 millisecond delay
      break;

    case 1: // Spinny wheel (4 LEDs on at a time)
      for (i = 0; i < NUM_LEDS; i++) { // For each LED...
        uint32_t c = 0;              // Assume pixel will be "off" color
        if (((offset + i) & 7) < 2) { // For each 8 pixels, 2 will be...
          c = color;                 // ...assigned the current color
        }
        pixels.setPixelColor(i, c);  // Set color of pixel 'i'
      }
      pixels.show();                 // Refresh LED states
      delay(50);                     // 50 millisecond delay
      offset++;                      // Shift animation by 1 pixel on next frame
      break;

    case 2: // Reverse Spinny wheel (4 LEDs on at a time)
      for (i = 0; i < NUM_LEDS; i++) { // For each LED...
        uint32_t c = 0;              // Assume pixel will be "off" color
        if (((offset + i) & 7) < 2) { // For each 8 pixels, 2 will be...
          c = color;                 // ...assigned the current color
        }
        pixels.setPixelColor((NUM_LEDS - i) % NUM_LEDS, c); // Set color of pixel 'i'
      }
      pixels.show();                 // Refresh LED states
      delay(50);                     // 50 millisecond delay
      offset++;                      // Shift animation by 1 pixel on next frame
      break;

    case 3: // rainbow spinny wheel
      for (i = 0; i < NUM_LEDS; i++) { // For each LED...
        uint32_t c = 0;              // Assume pixel will be "off" color
        if (((offset + i) & 7) < 2) { // For each 8 pixels, 2 will be...
          c = Wheel(((i * 256 / pixels.numPixels()) + i) & 255);
        }
        pixels.setPixelColor(i, c);  // Set color of pixel 'i'
      }
      pixels.show();                 // Refresh LED states
      delay(50);                     // 50 millisecond delay
      offset++;                      // Shift animation by 1 pixel on next frame
      break;

    case 4: // reverse rainbow spinny wheel
      for (i = 0; i < NUM_LEDS; i++) { // For each LED...
        uint32_t c = 0;              // Assume pixel will be "off" color
        if (((offset + i) & 7) < 2) { // For each 8 pixels, 2 will be...
          c = Wheel(((i * 256 / pixels.numPixels()) + i) & 255);
        }
        pixels.setPixelColor((NUM_LEDS - i) % NUM_LEDS, c); // Set color of pixel 'i'
      }
      pixels.show();                 // Refresh LED states
      delay(50);                     // 50 millisecond delay
      offset++;                      // Shift animation by 1 pixel on next frame
      break;


    case 5: // Random rainbow sparkles - just one LED on at a time!
      i = random(NUM_LEDS);           // Choose a random pixel
      pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + i) & 255));
      pixels.show();                  // Refresh LED states
      // Set same pixel to "off" color now but DON'T refresh...
      // it stays on for now...both this and the next random
      // pixel will be refreshed on the next pass.
      pixels.setPixelColor(i, 0);
      delay(10);                      // 10 millisecond delay
      break;

    case 6: // red white and blue sparkles
      i = random(NUM_LEDS);           // Choose a random pixel
      j = offset % 3;
      switch (j) {
        case 0:
          pixels.setPixelColor(i, pixels.Color(0, 0, 255)); // blue
          break;
        case 1:
          pixels.setPixelColor(i, pixels.Color(255, 0, 0)); // red
          break;
        case 2:
          pixels.setPixelColor(i, pixels.Color(255, 255, 255)); // white
          break;
      }
      offset += 1;
      pixels.show();                  // Refresh LED states
      // Set same pixel to "off" color now but DON'T refresh...
      // it stays on for now...both this and the next random
      // pixel will be refreshed on the next pass.
      pixels.setPixelColor(i, 0);
      delay(10);                      // 10 millisecond delay
      break;

    case 7: // red white and blue spinny
      for (i = 0; i < NUM_LEDS; i++) { // For each LED...
        uint32_t c = 0;              // Assume pixel will be "off" color
        if (((offset + i) & 7) < 2) { // For each 8 pixels, 2 will be...
          switch (offset % 3) {
            case 0:
              c = pixels.Color(10, 10, 255); // blue
              break;
            case 1:
              c = pixels.Color(255, 10, 10); // red
              break;
            case 2:
              c = pixels.Color(120, 120, 120); // white
              break;
          }
        }
        pixels.setPixelColor(i, c);  // Set color of pixel 'i'
      }
      pixels.show();                 // Refresh LED states
      delay(50);                     // 50 millisecond delay
      offset++;                      // Shift animation by 1 pixel on next frame
      break;

    case 8: //creverse red white and blue spinny
      for (i = 0; i < NUM_LEDS; i++) { // For each LED...
        uint32_t c = 0;              // Assume pixel will be "off" color
        if (((offset + i) & 7) < 2) { // For each 8 pixels, 2 will be...
          switch (offset % 3) {
            case 0:
              c = pixels.Color(10, 10, 255); // blue
              break;
            case 1:
              c = pixels.Color(255, 10, 10); // red
              break;
            case 2:
              c = pixels.Color(120, 120, 120); // white
              break;
          }
        }
        pixels.setPixelColor((NUM_LEDS - i) % NUM_LEDS, c); // Set color of pixel 'i'
      }
      pixels.show();                 // Refresh LED states
      delay(50);                     // 50 millisecond delay
      offset++;                      // Shift animation by 1 pixel on next frame
      break;

    default:
      // reset back to default.
      mode = 0;
      color = DEFAULT_COLOR;
      offset = 0;
      nr_colors = 0;
      break;
  }
  t = millis();                    // Current time in milliseconds
  if ((t - prevTime) > 8000) {     // Every 8 seconds...
    offset = 0;
    mode = random(MAX_MODES);                        // Advance to next animation mode
    color  = Wheel(random(255));                 // And change color
    pixels.clear();                // Set all pixels to 'off' state
    prevTime = t;                  // Record the time of the last mode change
  }
}
