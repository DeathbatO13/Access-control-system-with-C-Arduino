// Config.h
#ifndef CONFIG_H
#define CONFIG_H

// Pines del teclado 
#define KP_ROW_PIN_0 2
#define KP_ROW_PIN_1 3
#define KP_ROW_PIN_2 4
#define KP_ROW_PIN_3 5
#define KP_COL_PIN_0 6
#define KP_COL_PIN_1 7
#define KP_COL_PIN_2 8
#define KP_COL_PIN_3 9

// Pines LCD 
#define LCD_I2C_ADDR 0x3F   

// Actuadores
#define LOCK_PIN A2      // Relé o LED que representa la cerradura
#define BUZZER_PIN A3    // Buzzer piezo

// Lógica
#define MAX_PASSWORD_LENGTH 8
#define INPUT_TIMEOUT_MS 5000UL    // borrar entrada después de 5000 ms sin teclas
#define LOCKOUT_DURATION_MS 10000UL // bloqueo tras 3 fallos por 10000 ms
#define MAX_FAILED_ATTEMPTS 3

#endif
