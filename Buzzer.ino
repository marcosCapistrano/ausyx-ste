#define PIN_BUZZER 32

#define RE 294
#define MI 330
#define FA 349
#define SOL 392

#define SOFT_DELAY 10000
#define MEDIUM_DELAY 5000
#define HARD_DELAY 2000

#define SOFT_ATTEMPTS 2
#define MEDIUM_ATTEMPTS 2

int lastPlayed; //Guardará a ultima vez que o buzzer tocou
int tentativas = 0; // Guarda o numero de tentativas antes de desativar o alarme

void buzzer_setup() {
  pinMode(PIN_BUZZER, OUTPUT);

  lastPlayed = millis();
}

void buzzer_loop() {
  if (temperatura >= tempLimite) {
    if (!isAware) {
      int timeNow = millis();

      if (tentativas < SOFT_ATTEMPTS) {
        if (timeNow - lastPlayed >= SOFT_DELAY) {
          buzzer_play_soft();
        }
      } else if (tentativas < MEDIUM_ATTEMPTS) {
        if (timeNow - lastPlayed >= MEDIUM_DELAY) {
          buzzer_play_medium();
        }
      } else {
        if (timeNow - lastPlayed >= HARD_DELAY) {
          buzzer_play_hard();
        }
      }
    }
  } else {
    isAware = false;
  }
}

void buzzer_play_soft() {
  tom(RE, 100);
  tom(FA, 200);
  tom(SOL, 300);
  tom(MI, 400);
  tom(RE, 500);

  tentativas++;
  lastPlayed = millis();
}

void buzzer_play_medium() {
  tom(RE, 400);
  tom(MI, 200);
  tom(RE, 200);
  tom(MI, 200);

  tom(FA, 400);
  tom(SOL, 800);

  tentativas++;
  lastPlayed = millis();
}

void buzzer_play_hard() {
  tom(RE, 1000);
  tom(SOL, 1000);

  tentativas++;
  lastPlayed = millis();
}

void tom(int frequencia, int duracao) {
  float periodo = 1000.0 / frequencia; //Periodo em ms
  for (int i = 0; i < duracao / (periodo); i++) { //Executa a rotina de dentro o tanta de vezes que a frequencia desejada cabe dentro da duracao
    digitalWrite(PIN_BUZZER, HIGH);
    delayMicroseconds(periodo * 500); //Metade do periodo em ms
    digitalWrite(PIN_BUZZER, LOW);
    delayMicroseconds(periodo * 500);
  }
}
