// ControlAcceso.ino
#include <Arduino.h>
#include "Config.h"
#include "KeypadManager.h"
#include "DisplayManager.h"
#include "AccessController.h"

// Pines en arrays para KeypadManager
const byte rowPins[4] = { KP_ROW_PIN_0, KP_ROW_PIN_1, KP_ROW_PIN_2, KP_ROW_PIN_3 };
const byte colPins[4] = { KP_COL_PIN_0, KP_COL_PIN_1, KP_COL_PIN_2, KP_COL_PIN_3 };

// Objetos
KeypadManager keypad(rowPins, colPins);
DisplayManager display(LCD_I2C_ADDR);
AccessController access("1234"); // contraseña por defecto: "1234". Cámbiala aquí.

// Variables de entrada
String inputBuffer = "";
unsigned long lastInputTime = 0;

void setup() {
  pinMode(LOCK_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(LOCK_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.begin(9600);
  keypad.begin();
  display.begin();
  display.showWelcome();
}

void loop() {
  // Si está bloqueado, mostrar tiempo restante
  if (access.isLocked()) {
    unsigned long rem = access.lockRemainingMs();
    char buf[17];
    snprintf(buf, sizeof(buf), "Bloqueado: %lus", (rem+999)/1000);
    display.showMessage("Acceso denegado", String(buf));
    tone(BUZZER_PIN, 1000, 100); // alerta corta (opcional)
    delay(500);
    return;
  }

  char k = keypad.getKey();
  if (k != '\0') {
    lastInputTime = millis();
    // manejo de teclas
    if (k == 'C') {
      // borrar
      inputBuffer = "";
    } else if (k == '=') {
      // confirmar
      if (inputBuffer.length() > 0) {
        bool ok = access.verify(inputBuffer);
        if (ok) {
          display.showMessage("Acceso concedido", "");
          digitalWrite(LOCK_PIN, HIGH); // abrir
          // mantener abierto 5s
          delay(5000);
          digitalWrite(LOCK_PIN, LOW);
          display.showWelcome();
          inputBuffer = "";
        } else {
          // acceso denegado
          display.showMessage("Acceso denegado", "Intente otra vez");
          // sonido de error
          for (int i=0;i<2;i++){
            tone(BUZZER_PIN, 2000, 120);
            delay(150);
          }
          inputBuffer = "";
          delay(1000);
          display.showWelcome();
        }
      }
    } else {
      // tecla numérica u otra: agregar si no excede
      if (inputBuffer.length() < MAX_PASSWORD_LENGTH) {
        inputBuffer += k;
      }
    }
  }

  // mostrar entrada enmascarada en LCD
  String masked = "";
  for (unsigned int i=0;i<inputBuffer.length();i++) masked += '*';
  display.showInput(masked);

  // timeout para borrar entrada
  if (inputBuffer.length() > 0 && (millis() - lastInputTime) > INPUT_TIMEOUT_MS) {
    inputBuffer = "";
    display.showWelcome();
  }
}
