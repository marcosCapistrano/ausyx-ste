/*
 * Link placa ESP32: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
 */

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiAP.h>

#include <WebSocketsServer.h>

#include <U8g2lib.h>
#include <SPI.h>

bool isAware = false; //Guarda se alguem apertou o botão de silenciar
int temperatura = 0; // Valor recebido no WebSocketServer, enviado pelo sensor no ESP8266
int tempLimite = 100; // Valor setado pelo potenciometro

uint32_t lastComm = millis() / 1000;
bool hasCommOnce = false;

void setup(void) {
  Serial.begin(115200);
  
  lcd_setup();
  buzzer_setup();
  mutebutton_setup();

  xTaskCreatePinnedToCore(
      server_task, /* Function to implement the task */
      "Task1", /* Name of the task */
      10000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      5,  /* Priority of the task */
      NULL,  /* Task handle. */
      0); /* Core where the task should run */
}

void loop(void) {
  potentiometer_loop();
  lcd_draw();
  buzzer_loop();
}

/*
   Esta função existe para garantir que o teste: state_manager_get(TEMP_MASS) <= a - b
   Quando a < b, a subtração dos dois irá fazer o resultado causar um WRAP e bugar o resultado
*/
uint32_t safe_subtraction(uint32_t a, uint32_t b) {
  uint32_t diff;
  if (a < b) {
    diff = 0;
  } else {
    diff = a - b;
  }

  return diff;
}
