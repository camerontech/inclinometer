#include <SoftwareSerial.h>

SoftwareSerial mySerial(3,2);

const int XIN = 0;
const int YIN = 1;
const int ZIN = 2;

const int XMIN = 262;
const int XMAX = 398;
const int YMIN = 265;
const int YMAX = 403;

const int FLAT = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int FORWARD = 3;
const int BACK = 4;

const char* ORIENTATIONS[] = {"FLAT","LEFT","RIGHT","FORWARD","BACK"};
int orientation;
int x, y, z;
int xCalibrated, yCalibrated;
String xString, yString, output;
int outputLength = 0;

void setup() {
  orientation = getOrientation();

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

  x = analogRead(XIN);
  y = analogRead(YIN);

  Serial.print("x:");
  Serial.print(x, DEC);
  Serial.print(" y:");
  Serial.println(y, DEC);
  Serial.print("orientation: ");
  Serial.println(ORIENTATIONS[orientation]);

  xCalibrated = map(x, XMIN, XMAX, -90, 90);
  yCalibrated = map(y, YMIN, YMAX, -90, 90);

  xString = String(xCalibrated);
  yString = String(yCalibrated);

  updateDisplay();

  // Wait a quarter second so the numbers aren't flashing so fast
  delay(250);
}

int getOrientation() {
  int offset = 25;
  int xMid = (XMAX - XMIN) / 2 + XMIN;
  int yMid = (YMAX - YMIN) / 2 + YMIN;

  int x = analogRead(XIN);
  int y = analogRead(YIN);

  if (x > xMid-offset && x < xMid+offset) {
    if (y > yMid-offset && y < yMid+offset) {
      return FLAT;
    } else if (y > YMIN-offset && y < YMIN+offset) {
      return LEFT;
    } else {
      return RIGHT;
    }
  } else if (x > XMIN-offset && x < XMIN+offset) {
    return FORWARD;
  } else {
    return BACK;
  }
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

void updateDisplay() {
  // Pad for X value
  output = "   ";
  if (xString.length() == 1) {
    output += " ";
  }
  output += xString;

  // Write X value and degree sign
  mySerial.print(output);
  mySerial.write(223);

  outputLength = output.length() + 1;

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
  mySerial.write(223);

  outputLength += output.length() + 1;

  // Pad the rest of the line with blanks
  for (int i=outputLength; i<16; i++) {
    mySerial.print(" ");
  }
}
