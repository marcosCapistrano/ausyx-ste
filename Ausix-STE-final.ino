#include <Arduino.h>
#include <WiFi.h>
#include <WiFiAP.h>

#include <WebSocketsServer.h>

#include <U8g2lib.h>
#include <SPI.h>

bool isAware = false; //Guarda se alguem apertou o botão de silenciar
int temperatura = 0; // Valor recebido no WebSocketServer, enviado pelo sensor no ESP8266
int tempLimite = 100; // Valor setado pelo potenciometro

void setup(void) {
  Serial.begin(115200);
  
  server_setup();
  lcd_setup();
  buzzer_setup();
  mutebutton_setup();
}

void loop(void) {
  potentiometer_loop();
  server_loop();
  
  lcd_draw();
  buzzer_loop();
}
