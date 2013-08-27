// Thanks to http://bildr.org/2011/04/sensing-orientation-with-the-adxl335-arduino
// for finding the correct formula for converting the ADXL335 voltage to angles.

//#include <SoftwareSerial.h>

//SoftwareSerial Serial1(3,2);

// analog input pins
const int X_PIN = 0;
const int Y_PIN = 1;
const int Z_PIN = 2;

// max/min analog values
const int MIN = 405;
const int MAX = 615;

// ASCII character for degree symbol
const int DEGREE = 223;

void setup() {
  // set analogRead max to 3.3v instead of default 5v
  analogReference(EXTERNAL);

  // startup the serial ports
  Serial1.begin(9600);

  // wait for splash screen
  delay(500);

  // clear out anything that's on the display already
  clearDisplay();

  // write header
  Serial1.write("  PITCH   ROLL ");
}

void loop() {
  // sample the voltages
  int x = analogRead(X_PIN);
  int y = analogRead(Y_PIN);
  int z = analogRead(Z_PIN);

  // convert to range of -90 to +90 degrees
  int xAng = map(x, MIN, MAX, -90, 90);
  int yAng = map(y, MIN, MAX, -90, 90);
  int zAng = map(z, MIN, MAX, -90, 90);

  // convert radians to degrees
  int pitch = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  int roll = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);

  // convert left roll and forward pitch to negative degrees
  if (pitch > 180) {
    pitch = pitch - 360;
  }
  if (roll > 180) {
    roll = roll - 360;
  }

  // write the pitch and roll to the second line
  updateDisplay(pitch, roll);

  // Wait a quarter second so the numbers aren't flashing so fast
  delay(250);
}

void updateDisplay(int pitch, int roll) {
  moveToSecondLine();

  // convert int values to strings for output
  String pitchString = String(pitch);
  String rollString = String(roll);

  // pad spaces before pitch value
  String output = "   ";
  if (pitchString.length() == 1) {
    output += " ";
  }
  output += pitchString;

  // write pitch value
  Serial1.print(output);
  Serial1.write(DEGREE);

  int outputLength = output.length() + 1;

  // pad spaces before pitch value
  output = "";
  for (int i=outputLength; i<10; i++) {
    output += " ";
  }
  if (rollString.length() == 1) {
    output += " ";
  }
  output += rollString;

  // pad spaces before roll value
  Serial1.print(output);
  Serial1.write(DEGREE);

  outputLength += output.length() + 1;

  // fill the rest of the line with blanks
  for (int i=outputLength; i<16; i++) {
    Serial1.print(" ");
  }
}

void clearDisplay() {
  moveToFirstLine();
  Serial1.write("                ");
  Serial1.write("                ");
  moveToFirstLine();
}

void moveToFirstLine() {
  Serial1.write(254);
  Serial1.write(128);
}

void moveToSecondLine() {
  Serial1.write(254);
  Serial1.write(192);
}
