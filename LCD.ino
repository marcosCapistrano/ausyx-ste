#define FONT_BIG u8g2_font_inr46_mn
#define FONT_SMALL u8g2_font_5x8_tf
#define FONT_MEDIUM u8g2_font_7x14_tf

static uint8_t speaker_bits[] = {
  0xFF, 0xFF, 0xFF, 0x01, 0xFF, 0xFB, 0xE8, 0x01, 0xFF, 0x6F, 0xFF, 0x01, 
  0x0F, 0xFE, 0xFF, 0x01, 0xEF, 0xFF, 0xDF, 0x01, 0xFF, 0xFF, 0xFF, 0x01, 
  0xFF, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0x01, 
  0xFF, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0xEF, 0x01, 0xFF, 0xFF, 0xDF, 0x01, 
  0x0F, 0xFF, 0xFF, 0x01, 0xFF, 0x6D, 0xFF, 0x01, 0xFF, 0xFB, 0xE0, 0x01, 
  };

static uint8_t muted_bits[] = {
  0xFF, 0xFF, 0xFF, 0x03, 0xFF, 0x7F, 0xFE, 0x03, 0xFF, 0x7F, 0xFE, 0x03, 
  0xFF, 0x77, 0xFA, 0x03, 0x7F, 0x7F, 0xFE, 0x03, 0xFF, 0xFF, 0xFF, 0x03, 
  0xFF, 0xFF, 0xFF, 0x03, 0xFF, 0x7F, 0xFF, 0x03, 0xFF, 0x7F, 0xFF, 0x03, 
  0xFF, 0xFF, 0xFF, 0x03, 0xFF, 0xFF, 0xFF, 0x03, 0xEF, 0x7F, 0xFF, 0x03, 
  0xFF, 0x7F, 0xFF, 0x03, 0xFF, 0x7B, 0xFE, 0x03, 0xFF, 0x7F, 0xFE, 0x03, 
  };

U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 14, /* data=*/ 13, /* CS=*/ 15, /* reset=*/ 26); // Feather HUZZAH ESP8266, E=clock=14, RW=data=13, RS=CS

String tempString = "0";
String limitString = "ALARME: 0°C";

char tempBuf[3];
int tempBufLen = 3;
char tempLimiteBuf[25];
int tempLimiteBufLen = 25;

int tempStrX = 45;
int tempLimiteStrX = 39;

void lcd_setup(void) {
  u8g2.begin();
}

void lcd_draw(void) {
  u8g2.clearBuffer();

  u8g2.setDrawColor(1);
  u8g2.setFont(FONT_BIG);

  memset(tempBuf, 0, 3);
  tempString = String(temperatura);
  tempBufLen = tempString.length();
  tempString.toCharArray(tempBuf, 3);
  tempStrX = 64-(38*tempBufLen/2);
  u8g2.drawStr(tempStrX, 48, tempBuf);

  u8g2.setDrawColor(1);
  u8g2.setFont(FONT_MEDIUM);
  u8g2.drawUTF8(107, 15, "°C");

  u8g2.setDrawColor(1);
  u8g2.drawBox(23, 52, 81, 12);

  u8g2.setDrawColor(0);
  u8g2.setFont(FONT_SMALL);

  memset(tempLimiteBuf, 0, 25);
  limitString = "ALARME: " + String(tempLimite) + "°C";
  tempLimiteBufLen = limitString.length();
  limitString.toCharArray(tempLimiteBuf, 25);
  tempLimiteStrX = 64-(5*tempLimiteBufLen/2);
  u8g2.drawUTF8(tempLimiteStrX, 61, tempLimiteBuf);

  if (temperatura >= tempLimite) {
    if (isAware) {
      u8g2.drawXBM(26, 15, 26, 15, muted_bits);
    } else {
      u8g2.drawXBM(26, 15, 26, 15, speaker_bits);
    }
  }

  u8g2.sendBuffer();
}
