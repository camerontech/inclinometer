Arduino Inclinometer
====================

This sketch uses an accelerometer and serial-enabled 16x2 LCD screen to measure
and display pitch and roll of a vehicle. An inclinometer is usually used in
offroading to determine how close you are to having a very bad day.

![photo](https://farm8.staticflickr.com/7330/9578822489_0db79b4148_o.jpg)

Here's what it looks like prototyped:

![photo](http://cannikin.github.com/arduino_inclinometer/photo.jpg?1)

And a quick video in action: http://www.youtube.com/watch?v=Q_Gq_8f8r2c

Features
--------

The inclinometer reads the X and Y values from the accelerometer and translates
them into PITCH (forward and back tilt) and ROLL (left and right tilt).
However, since we're only measuring acceleration we will get false readings when
the sensor itself is in motion (like when you're driving in a car). To get a
"true" reading of your pitch and roll you'll need to stop moving.

Equipment
---------
* 1 x Arduino or compatible board https://www.sparkfun.com/products/11021
* 1 x 16x2 serial-enabled LCD https://www.sparkfun.com/products/9395
* 1 x ADXL335 triple axis accelerometer https://www.sparkfun.com/products/9269

Wiring
------
Connect the accelerometer to 3.3V, GND, X to analog pin 0 and Y to analog pin 1
and Z to analog pin 2.

Connect 5V to one leg of the push button. Connect the other leg to a 10K
pull-down resistor to ground and to digital pin 7.

Connect the 3.3V output to AREF. This sets the maximum voltage to be expected
when doing an analogRead. In our case that makes 3.3V = 1024.

Connect the LCD to 5V, GND. Connect RX to pin 1 on the Arduino _after_ uploading your sketch. The LCD uses the same pin as the USB connector when uploading code
so to avoid scrambling your LCD don't connect it until after your sketch is
uploaded.

![layout](http://cannikin.github.com/arduino_inclinometer/inclinometer-layout.png?6)

The LCD screen in the diagram is a parallel one, but I'm wiring it as if it
was a Sparkfun SerLCD: 5V, GND and RX are the only pins needed.

Bonus
-----
If you plan to use this in your vehicle you may need some help getting the
correct voltages to your Arduino and accelerometer. In my truck I was able to
tap into the wires for the overhead lights that measured about 12.8v. The
Arduino I'm using expects to receive 5v and doesn't have a dedicated 3.3v
output. So I wired up a regulator package that takes 12v and outputs both 5v and
3.3v.

![layout](http://cannikin.github.com/arduino_inclinometer/voltage_regulator-layout.png?1)
