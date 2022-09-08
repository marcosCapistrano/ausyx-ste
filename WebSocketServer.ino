const char *ssid = "MTF-01";
const char *password = "AusyxSolucoes";
WebSocketsServer webSocket = WebSocketsServer(80);

void server_task(void *pvParameters) {
  Serial.println();
  Serial.println("Configurando access point...");

  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(ssid, password);
  Serial.println(WiFi.status());
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  Serial.println("Server started!");

  webSocket.begin();
  webSocket.onEvent(handle_events);

  for(;;) {
    webSocket.loop();
    vTaskDelay(100);
  }
}

void handle_events(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
      }
      break;
    case WStype_TEXT:
      if (length > 0) {
        temperatura = atoi((const char *) payload);
        if(temperatura < 0) temperatura = 0;

        lastComm = millis() / 1000;
        hasCommOnce = true;
        
//        Serial.printf("Temperatura setada para: %d\n",temperatura);

        // send message to client
        // webSocket.sendTXT(num, "message here");

        // send data to all connected clients
        // webSocket.broadcastTXT("message here");
      }
      break;
    case WStype_BIN:
      Serial.printf("[%u] get binary length: %u\n", num, length);
      // send message to client
      // webSocket.sendBIN(num, payload, length);
      break;
    case WStype_ERROR:
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
      break;
  }

}
