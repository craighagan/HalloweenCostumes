

# Pinewood Derby Practice Track Timer

This implements a photosensor based timer for a pinewood derby practice track.

Need:
2x 10kohm resistors - https://smile.amazon.com/gp/product/B00B5RJF1M
2x Photoresistors - https://smile.amazon.com/gp/product/B008QVE9BG
1x Arduino Uno or compatible - https://smile.amazon.com/Arduino-Uno-R3-Microcontroller-A000066
1x SainSmart LCD 1602 Keypad Shield for Arduino Due UNO R3 Mega2560 R3 Duemilanove - https://smile.amazon.com/gp/product/B006OVYI1G

Circuit:

Start track   End Track
 P            P
 ||           ||    +--------------- A1
 ||           |+----+----- 10k ---- GND
 ||           +--------------------- 5v
 |+-----------------+------ 10k --- GND
 |                  +--------------- A2
 +---------------------------------- 5v

P:   Photoresistor
A1:  Arduino A1 input
A2:  Arduino A2 input
5v:  Arduino 5v supply pin
GND: Arduino GND pin 


