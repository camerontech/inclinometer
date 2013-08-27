// Thanks to http://bildr.org/2011/04/sensing-orientation-with-the-adxl335-arduino
// for finding the correct formula for converting the ADXL335 voltage to angles.

#include <SoftwareSerial.h>

SoftwareSerial mySerial(3,2);

// analog input pins
const int X_IN = 0;
const int Y_IN = 1;
const int Z_IN = 2;
const int TARE_IN = 7;

// max/min analog values
const int MIN = 405;
const int MAX = 615;

int xmax = 000;
int xmin = 999;
int ymax = 000;
int ymin = 999;
int zmax = 000;
int zmin = 999;

// ASCII character for degree symbol
const int DEGREE = 223;

// tare values that we want to save between loops
int xTare = 0;
int yTare = 0;
int zTare = 0;

void setup() {
  // Setup tare pin as an input
  pinMode(TARE_IN, INPUT);
  // Enable internal pull-up resistor
  digitalWrite(TARE_IN, HIGH);

  Serial.begin(9600);
  mySerial.begin(9600);
  analogReference(EXTERNAL);

  // wait for splash screen
  delay(500);

  clearDisplay();

  // write header
  mySerial.write("  PITCH   ROLL ");
}

void loop() {
  moveToSecondLine();

  // if the button is pressed, tare the current values
  if (digitalRead(TARE_IN) == LOW) {
    tare();
  }

  // sample the voltages
  int x = analogRead(X_IN) - xTare;
  int y = analogRead(Y_IN) - yTare;
  int z = analogRead(Z_IN) - zTare;

  // convert to range of -90 to +90 degrees
  int xAng = map(x, MIN, MAX, -90, 90);
  int yAng = map(y, MIN, MAX, -90, 90);
  int zAng = map(z, MIN, MAX, -90, 90);

  // do some math to convert radians to degrees
  int pitch = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  int roll = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);

  if (pitch > 180) {
    pitch = pitch - 360;
  }
  if (roll > 180) {
    roll = roll - 360;
  }

  Serial.print("x:");
  Serial.print(x, DEC);
  Serial.print(" y:");
  Serial.print(y, DEC);
  Serial.print(" z:");
  Serial.println(z, DEC);

  updateDisplay(pitch, roll);

  // Wait a quarter second so the numbers aren't flashing so fast
  delay(250);
}

void tare() {
  int x = analogRead(X_IN);
  int y = analogRead(Y_IN);
  int z = analogRead(Z_IN);

  xTare = x - (MAX - MIN) / 2 + MIN;
  yTare = y - (MAX - MIN) / 2 + MIN;
  zTare = z - (MAX - MIN) / 2 + MIN;
}

void clearDisplay() {
  moveToFirstLine();
  mySerial.write("                ");
  mySerial.write("                ");
  moveToFirstLine();
}

void moveToFirstLine() {
  mySerial.write(254);
  mySerial.write(128);
}

void moveToSecondLine() {
  mySerial.write(254);
  mySerial.write(192);
}

void updateDisplay(int pitch, int roll) {
  String pitchString = String(pitch);
  String rollString = String(roll);

  // Pad for X value
  String output = "   ";
  if (pitchString.length() == 1) {
    output += " ";
  }
  output += pitchString;

  // Write X value and degree sign
  mySerial.print(output);
  mySerial.write(DEGREE);

  int outputLength = output.length() + 1;

  // Pad for Y value
  output = "";
  for (int i=outputLength; i<10; i++) {
    output += " ";
  }
  if (rollString.length() == 1) {
    output += " ";
  }
  output += rollString;

  // Write Y value and degree sign
  mySerial.print(output);
  mySerial.write(DEGREE);

  outputLength += output.length() + 1;

  // Fill the rest of the line with blanks
  for (int i=outputLength; i<16; i++) {
    mySerial.print(" ");
  }
}
