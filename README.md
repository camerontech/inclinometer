Arduino Inclinometer
====================

This sketch uses an accelerometer and serial-enabled 16x2 LCD screen to measure
pitch and roll of a vehicle, usually for offroading when doing things like this:

![photo](http://farm8.staticflickr.com/7330/9578822489_0db79b4148_o.jpg)

And everything laid out on a protoboard:

![photo](http://cannikin.github.io/arduino_inclinometer/photo.jpg?1)

And a quick video in action: http://www.youtube.com/watch?v=Q_Gq_8f8r2c

Equipment
---------
* 1 x Ardunio or compatible board https://www.sparkfun.com/products/11021
* 1 x SerLCD from Sparkfun https://www.sparkfun.com/products/9395
* 1 x ADXL335 triple axis accelerometer https://www.sparkfun.com/products/9269

Wiring
------
Connect the LCD to 5V, GND and digital pin 2.

Connect the accelerometer to 3.3V, GND, X to analog pin 0 and Y to analog pin 1.
