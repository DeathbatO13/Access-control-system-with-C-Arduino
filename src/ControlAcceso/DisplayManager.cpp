#include "DisplayManager.h"
#include "Config.h"

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
  _lcd.print("Sistema Acceso");
  _lcd.setCursor(0,1);
  _lcd.print("Ingrese clave:");
}

void DisplayManager::showInput(const String& maskedInput){
  _lcd.setCursor(0,1);
  String s = maskedInput;
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
