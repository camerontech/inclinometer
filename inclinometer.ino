#include <SoftwareSerial.h>

SoftwareSerial mySerial(3,2);

// analog input pins
const int X_IN = 0;
const int Y_IN = 1;
const int TARE_IN = 7;

// max/min analog values
const int XMIN = 262;
const int XMAX = 398;
const int XMID = XMIN + (XMAX - XMIN) / 2;
const int YMIN = 265;
const int YMAX = 403;
const int YMID = YMIN + (YMAX - YMIN) / 2;

// ASCII character for degree symbol
const int DEGREE = 223;

// tare values that we want to save between loops
int xTare = 0;
int yTare = 0;

void setup() {
  // Setup tare pin as an input
  pinMode(TARE_IN, INPUT);
  // Enable internal pull-up resistor
  digitalWrite(TARE_IN, HIGH);

  Serial.begin(9600);
  mySerial.begin(9600);

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

  int x = analogRead(X_IN);
  int y = analogRead(Y_IN);

  Serial.print("x:");
  Serial.print(x, DEC);
  Serial.print(" y:");
  Serial.println(y, DEC);

  int xCalibrated = map(x-xTare, XMIN, XMAX, -90, 90);
  int yCalibrated = map(y-yTare, YMIN, YMAX, -90, 90);

  updateDisplay(xCalibrated, yCalibrated);

  // Wait a quarter second so the numbers aren't flashing so fast
  delay(250);
}

void tare() {
  int x = analogRead(X_IN);
  int y = analogRead(Y_IN);

  xTare = x - XMID;
  yTare = y - YMID;
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

void updateDisplay(int x, int y) {
  String xString = String(x);
  String yString = String(y);

  // Pad for X value
  String output = "   ";
  if (xString.length() == 1) {
    output += " ";
  }
  output += xString;

  // Write X value and degree sign
  mySerial.print(output);
  mySerial.write(DEGREE);

  int outputLength = output.length() + 1;

  // Pad for Y value
  output = "";
  for (int i=outputLength; i<10; i++) {
    output += " ";
  }
  if (yString.length() == 1) {
    output += " ";
  }
  output += yString;

  // Write Y value and degree sign
  mySerial.print(output);
  mySerial.write(DEGREE);

  outputLength += output.length() + 1;

  // Fill the rest of the line with blanks
  for (int i=outputLength; i<16; i++) {
    mySerial.print(" ");
  }
}
