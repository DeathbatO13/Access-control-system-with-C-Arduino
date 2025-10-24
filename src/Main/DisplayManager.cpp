// DisplayManager.cpp
#include "DisplayManager.h"
#include "Config.h"

// CONSTRUCTOR CORREGIDO: Versión de 3 argumentos compatible con tu librería
// _lcd(Dirección, Columnas, Filas)
DisplayManager::DisplayManager(uint8_t address)
: _lcd(address, 16, 2) 
{} 

void DisplayManager::begin(){
  _lcd.init();
  _lcd.backlight();
  showWelcome();
}

void DisplayManager::showWelcome(){
  _lcd.clear();
  _lcd.setCursor(0,0);
  _lcd.print(F("Access System")); 
  _lcd.setCursor(0,1); // Fila 1 (segunda línea)
  _lcd.print(F("Enter password:")); 
}

void DisplayManager::showInput(const String& maskedInput){
  // Borra y reescribe solo la segunda línea
  _lcd.setCursor(0,1); 
  String s = maskedInput;
  // Rellena con espacios para limpiar la línea
  while (s.length() < 16) s += ' ';
  _lcd.print(s);
}

void DisplayManager::showMessage(const String& line1, const String& line2){
  _lcd.clear();
  _lcd.setCursor(0,0);
  _lcd.print(line1.substring(0,16));
  _lcd.setCursor(0,1);
  _lcd.print(line2.substring(0,16));
}

void DisplayManager::clear(){
  _lcd.clear();
}