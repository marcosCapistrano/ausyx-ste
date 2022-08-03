#define PIN_BUZZER 32

#define SOFT_DELAY 10000
#define MEDIUM_DELAY 5000
#define HARD_DELAY 2000

#define SOFT_ATTEMPTS 2
#define MEDIUM_ATTEMPTS 2

int lastPlayed; //Guardará a ultima vez que o buzzer tocou
int tentativas = 0; // Guarda o numero de tentativas antes de desativar o alarme

void buzzer_setup() {
  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_BUZZER, HIGH);

  lastPlayed = millis();
}

void buzzer_loop() {
  if (temperatura > tempLimite) {
    if (!isAware) {
      int timeNow = millis();

      if (tentativas < SOFT_ATTEMPTS) {
        if (timeNow - lastPlayed >= SOFT_DELAY) {
          buzzer_play_soft();
        }
      } else if (tentativas < SOFT_ATTEMPTS + MEDIUM_ATTEMPTS) {
        if (timeNow - lastPlayed >= MEDIUM_DELAY) {
          buzzer_play_medium();
        }
      } else {
        if (timeNow - lastPlayed >= HARD_DELAY) {
          buzzer_play_hard();
        }
      }
    } else {
      digitalWrite(PIN_BUZZER, HIGH);
      tentativas = 0;
    }
  } else {
    isAware = false;
    tentativas = 0;
    digitalWrite(PIN_BUZZER, HIGH);
  }
}

void buzzer_play_soft() {
  digitalWrite(PIN_BUZZER, LOW);
  delay(250);
  digitalWrite(PIN_BUZZER, HIGH);

  tentativas++;
  lastPlayed = millis();
}

void buzzer_play_medium() {
  digitalWrite(PIN_BUZZER, LOW);
  delay(1000);
  digitalWrite(PIN_BUZZER, HIGH);

  tentativas++;
  lastPlayed = millis();
}

void buzzer_play_hard() {
  digitalWrite(PIN_BUZZER, LOW);
}
