Arduino Inclinometer
====================

This sketch uses an accelerometer and serial-enabled 16x2 LCD screen to measure
and display pitch and roll of a vehicle. An inclinometer is usually use in
offroading to determine how close you are to having a very bad day.

![photo](https://farm8.staticflickr.com/7330/9578822489_0db79b4148_o.jpg)

Here's what it looks like prototyped:

![photo](https://cannikin.github.io/arduino_inclinometer/photo.jpg?1)

And a quick video in action: http://www.youtube.com/watch?v=Q_Gq_8f8r2c

Features
--------

The inclinometer reads the X and Y values from the accelerometer and translates
them into PITCH (forward and back tilt) and ROLL (left and right tilt).
However, since we're only measuring acceleration we will get false readings when
the sensor itself is in motion (like when you're driving in a car). To get a
"true" reading of your pitch and roll you'll need to stop moving.

The sensor's idea of 0° on the X and Y axes is set from the factory and your
initial readings may be a bit off from that if the sensor is not mounted
perfectly level (according to the sensor) in both axes. To compensate for this a
primitive "tare" has been added (press the button for a second) that takes the
current values and tells the system to treat them as 0° instead of the factory
defaults. This isn't ideal and effort should be taken to mount the sensor as
close to 0° as possible. If mounted in your car, stop the vehicle on what feels
like the flattest orientation possible and then tweak the sensor mount until you
read 0° for both measurements.

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

![layout](https://cannikin.github.com/arduino_inclinometer/inclinometer-layout.png?2)

The LCD screen in the diagram is a parallel one, but I'm wiring it as if it
was a Sparkfun SerLCD: 5V, GND and RX are the only pins needed.
