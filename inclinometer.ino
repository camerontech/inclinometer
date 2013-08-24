#include <SoftwareSerial.h>

SoftwareSerial mySerial(3,2);

const int XIN = 0;
const int YIN = 1;
const int ZIN = 2;

int x, y, z;
int xTare, yTare, zTare;
int xCalibrated, yCalibrated, zCalibrated;
String xString, yString, zString, output;
int outputLength = 0;

void setup() {
  // Set X/Y axis to 0 degrees
  tare();
  
  mySerial.begin(9600);
  
  // wait for splash screen
  delay(500);

  clearDisplay();
  
  // write header
  mySerial.write("  PITCH   ROLL  ");
}

void loop() {
  moveToSecondLine();
  
  x = analogRead(XIN);
  y = analogRead(YIN);
  
  xCalibrated = map(abs(x - xTare), 0, 67, 0, 90);
  yCalibrated = map(abs(y - yTare), 0, 69, 0, 90);
  
  xString = String(xCalibrated);
  yString = String(yCalibrated);

  // Pad for X value
  output = "   ";
  if (xString.length() == 1) {
    output += " ";
  }
  output += xString;
  
  // Write X value
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
  
  // Write Y value
  mySerial.print(output);
  mySerial.write(223);
  
  outputLength += output.length() + 1;
  
  // Pad the rest of the line with blanks
  output = "";
  for (int i=outputLength; i<16; i++) {
    output += " ";
  }
  
  // Write blanks
  mySerial.print(output);

  // Wait a quarter second so the numbers aren't flashing so fast
  delay(250);
}

void tare() {
  xTare = analogRead(XIN);
  yTare = analogRead(YIN);
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
