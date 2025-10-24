// DisplayManager.h

#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <Arduino.h>
#include <Wire.h>

#include <LiquidCrystal_I2C.h> 
#include "Config.h" 

class DisplayManager {
public:

  DisplayManager(uint8_t address = 0x3F); 
  void begin();
  void showWelcome();
  void showInput(const String& maskedInput);
  void showMessage(const String& line1, const String& line2 = "");
  void clear();
private:
  // Cambiar el objeto de _display a _lcd:
  LiquidCrystal_I2C _lcd;
};

#endif
