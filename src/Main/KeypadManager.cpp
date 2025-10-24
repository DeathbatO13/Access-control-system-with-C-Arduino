// KeypadManager.cpp
#include "KeypadManager.h"
#include <Keypad.h>
#include "Config.h"

// Matriz de teclas 4x4
static const char keys[4][4] = {
  { '7','8','9','/' },
  { '4','5','6','*' },
  { '1','2','3','-' },
  { 'C','0','=','+' }
};

static byte rowPinsInternal[4];
static byte colPinsInternal[4];
static Keypad* keypad = nullptr;

KeypadManager::KeypadManager(const byte* rowPins, const byte* colPins) : _rowPins(rowPins), _colPins(colPins) {
  // Copiar pines a arrays internos para Keypad
  for (int i=0;i<4;i++){
    rowPinsInternal[i] = _rowPins[i];
    colPinsInternal[i] = _colPins[i];
  }
}

void KeypadManager::begin(){
  if (keypad == nullptr) {
    keypad = new Keypad( makeKeymap(keys), rowPinsInternal, colPinsInternal, 4, 4 );
  }
}

char KeypadManager::getKey(){
  if (!keypad) return '\0';
  char k = keypad->getKey();
  if (k) return k;
  return '\0';
}
