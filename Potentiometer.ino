#define PIN_POTENTIOMETER 36
#define MIN_VALUE 0
#define MAX_VALUE 99

#define SAMPLES 15

int reading;    //Guarda o valor lido do ADC, antes de se mapear de 0-4095 para MIN_VALUE-MAX_VALUE
int count = 0; //Guarda quantas vezes o ADC foi lido, após (SAMPLES) vezes o valor é atualizado
int soma = 0, media = 0;

void potentiometer_setup(void) {
//  pinMode(PIN_POTENTIOMETER, INPUT);
}

/*
   Cada vez que rodar o LOOP do arduino, essa função é chamada, para que n]ao haja bloqueio do servidor/outras coisas, não se utiliza um loop FOR ou WHILE,
   mas sim uma variavel count que após esta função rodar SAMPLES vezes, ele atualiza o valor do tempLimite
*/
void potentiometer_loop(void) {
  reading = analogRead(PIN_POTENTIOMETER);
  soma += reading;

  if (count >= SAMPLES) {   
    media = soma / (SAMPLES + 1);
    tempLimite = map(media, 0, 4095, MIN_VALUE, MAX_VALUE);
     
    count = 0;
    soma = media;
  }

  count++;
}
