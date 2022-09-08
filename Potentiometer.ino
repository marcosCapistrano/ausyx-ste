#define PIN_IN1 33
#define PIN_IN2 34

#define MIN_VALUE 0
#define MAX_VALUE 100

RotaryEncoder *encoder = nullptr;
int baseLimitValue = 0;

IRAM_ATTR void checkPosition()
{
  encoder->tick(); // just call tick() to check the state.
}

void potentiometer_setup(void) {
  encoder = new RotaryEncoder(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::FOUR3);
  baseLimitValue = state_manager_get_limit();

  // register interrupt routine
  attachInterrupt(digitalPinToInterrupt(PIN_IN1), checkPosition, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_IN2), checkPosition, CHANGE);
}

/*
   Cada vez que rodar o LOOP do arduino, essa função é chamada, para que n]ao haja bloqueio do servidor/outras coisas, não se utiliza um loop FOR ou WHILE,
   mas sim uma variavel count que após esta função rodar SAMPLES vezes, ele atualiza o valor do tempLimite
*/
void potentiometer_loop(void) {
  static int pos = 0;
  encoder->tick(); // just call tick() to check the state.

  int newPos = encoder->getPosition();

  if (newPos != pos) {
    int newLimit = baseLimitValue;
    newLimit += newPos;

    if (newLimit < MIN_VALUE) {
      newLimit = MIN_VALUE;
    } else if (newLimit > MAX_VALUE) {
      newLimit = MAX_VALUE;
    }

    state_manager_set_limit(newLimit);

    pos = newPos;
  }
}
