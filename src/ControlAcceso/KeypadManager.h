// KeypadManager.h
#ifndef KEYPADMANAGER_H
#define KEYPADMANAGER_H

#include <Arduino.h>

class KeypadManager {
public:
  KeypadManager(const byte* rowPins, const byte* colPins);
  void begin();
  char getKey(); // devuelve '\0' si no hay tecla nueva
private:
  const byte* _rowPins;
  const byte* _colPins;
};

#endif