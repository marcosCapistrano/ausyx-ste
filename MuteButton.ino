#define PIN_BUTTON 32

void IRAM_ATTR isr() {
    isAware = true;
}

void mutebutton_setup() {
  pinMode(PIN_BUTTON, INPUT_PULLDOWN);
  attachInterrupt(PIN_BUTTON, isr, RISING);
}
