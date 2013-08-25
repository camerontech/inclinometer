Arduino Inclinometer
====================

This sketch uses an accelerometer and serial-enabled 16x2 LCD screen to measure
and display pitch and roll of a vehicle. An inclinometer is usually use in
offroading to determine how close you are to having a very bad day.

![photo](http://farm8.staticflickr.com/7330/9578822489_0db79b4148_o.jpg)

Here's what it looks like prototyped:

![photo](http://cannikin.github.io/arduino_inclinometer/photo.jpg?1)

And a quick video in action: http://www.youtube.com/watch?v=Q_Gq_8f8r2c

Equipment
---------
* 1 x Arduino or compatible board https://www.sparkfun.com/products/11021
* 1 x 16x2 serial-enabled LCD https://www.sparkfun.com/products/9395
* 1 x ADXL335 triple axis accelerometer https://www.sparkfun.com/products/9269

Wiring
------
Connect the LCD to 5V, GND and digital pin 2. (The current sketch uses the
SoftwareSerial library to write to the LCD so that we don't have to
connect/disconnect the screen from pins 0 and 1 when pushing new code, and also
so we can use the Arduino serial monitor for debugging.)

Connect the accelerometer to 3.3V, GND, X to analog pin 0 and Y to analog pin 1.

Connect 5V to one leg of the push button. Connect the other leg to a 10K
pull-down resistor to ground and to digital pin 7.

![layout](https://cannikin.github.com/arduino_inclinometer/inclinometer-layout.png)
