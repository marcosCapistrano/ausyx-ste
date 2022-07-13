#define FONT_BIG u8g2_font_inr46_mn
#define FONT_SMALL u8g2_font_5x8_tf
#define FONT_MEDIUM u8g2_font_7x14_tf

U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 14, /* data=*/ 13, /* CS=*/ 15, /* reset=*/ 26); // Feather HUZZAH ESP8266, E=clock=14, RW=data=13, RS=CS

String tempString = "0";
String limitString = "ALARME: 0°C";
 char tempBuf[3];
 char tempLimiteBuf[25];

void lcd_setup(void) {
  u8g2.begin();
}

void lcd_draw(void) {
  u8g2.clearBuffer();

  u8g2.setDrawColor(1);
  u8g2.setFont(FONT_BIG);

  tempString = String(temperatura);
  tempString.toCharArray(tempBuf, 3);
  u8g2.drawStr(26, 48, tempBuf);

  u8g2.setDrawColor(1);
  u8g2.setFont(FONT_MEDIUM);
  u8g2.drawUTF8(107, 15, "°C");

  u8g2.setDrawColor(1);
  u8g2.drawBox(23, 52, 81, 12);

  u8g2.setDrawColor(0);
  u8g2.setFont(FONT_SMALL);

  limitString = "ALARME: " + String(tempLimite) + "°C";
  limitString.toCharArray(tempLimiteBuf, 25);
  u8g2.drawUTF8(32, 61, tempLimiteBuf);

  u8g2.sendBuffer();
}
