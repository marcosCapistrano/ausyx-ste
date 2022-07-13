#define PIN_BUTTON 5

void IRAM_ATTR isr() {
    isAware = true;

    Serial.println("is aware!");
}

void mutebutton_setup() {
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  attachInterrupt(PIN_BUTTON, isr, FALLING);
}
