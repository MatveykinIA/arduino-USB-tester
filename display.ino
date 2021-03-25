// SCK - A5
// SDA - A4

/*
  SSD1306AsciiAvrI2c oled;

  void displaySetup() {
  oled.begin(&Adafruit128x64, 0x3C);
  }

  void displayLoop() {
  float v = adcV();
  float a = adcA();
  unsigned long c = adcC();

  // TimesNewRoman16
  oled.setFont(fixed_bold10x15);
  oled.clear();
  oled.set1X();
  oled.print("");
  oled.print(v);
  oled.print("V  ");
  if (sdIsInited()) {
    oled.println("SD+");
  } else {
    oled.println("SD-");
  }
  oled.print("");
  oled.print(a);
  oled.println("A");


  oled.print("");
  oled.print(v * a);
  oled.println("W");
  oled.print("");
  oled.print(c);
  oled.println("mAh");
  }
*/
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);

const uint8_t displayBitmap[] PROGMEM = {
  // '16', 16x16px
  /*0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf8, 0x0f, 0xf8, 0x0f, 0xf8, 0x71, 0xc7, 0x71, 0xc7,
    0x71, 0xc7, 0x7e, 0x3f, 0x7e, 0x3f, 0x7e, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00*/

  // '32', 32x32px
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0x80,
  0x01, 0xff, 0xff, 0x80, 0x01, 0xff, 0xff, 0x80, 0x01, 0xff, 0xff, 0x80, 0x01, 0xff, 0xff, 0x80,
  0x01, 0xff, 0xff, 0x80, 0x7e, 0x07, 0xe0, 0x7e, 0x7e, 0x07, 0xe0, 0x7e, 0x7e, 0x07, 0xe0, 0x7e,
  0x7e, 0x07, 0xe0, 0x7e, 0x7e, 0x07, 0xe0, 0x7e, 0x7e, 0x07, 0xe0, 0x7e, 0x7f, 0xf8, 0x1f, 0xfe,
  0x7f, 0xf8, 0x1f, 0xfe, 0x7f, 0xf8, 0x1f, 0xfe, 0x7f, 0xf8, 0x1f, 0xfe, 0x7f, 0xf8, 0x1f, 0xfe,
  0x7f, 0xf8, 0x1f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void displaySetup() {
  u8g.setRot180();
  u8g.firstPage();
  do {
  } while ( u8g.nextPage() );
}

void displayLoop() {
  float v = adcV();
  float a = adcA();
  float rl = adcRl();
  unsigned int t = adcTime();
  unsigned long mWh = adcMWh();
  unsigned long c = adcC();
  u8g.firstPage();
  do {
    u8g.drawBitmapP(80, 0, 4, 32, displayBitmap);

    u8g.setPrintPos(0, 13);
    u8g.setFont(u8g_font_profont17);
    u8g.print(v);
    u8g.setFont(u8g_font_profont12);
    u8g.print("V");

    u8g.setPrintPos(0, 28);
    u8g.setFont(u8g_font_profont17);
    u8g.print(a);
    u8g.setFont(u8g_font_profont12);
    u8g.print("A");

    u8g.setPrintPos(0, 39);
    u8g.print(v * a);
    u8g.print(" W");
    u8g.setPrintPos(64, 39);
    if (t / 60 < 10) {
      u8g.print("0");
    }
    u8g.print(t / 60);
    u8g.print(":");
    if (t % 60 < 10) {
      u8g.print("0");
    }
    u8g.print(t % 60);
    u8g.print(" T");

    u8g.setPrintPos(0, 50);
    u8g.print(c);
    u8g.print(" mAh");
    u8g.setPrintPos(64, 50);
    u8g.print(rl);
    u8g.print(" ohm");

    u8g.setPrintPos(0, 61);
    u8g.print(mWh);
    u8g.print(" mWh");
    u8g.setPrintPos(64, 61);
    if (sdIsInited()) {
      u8g.print(sdGetFileName());
    } else {
      u8g.print("SD-");
    }


  } while ( u8g.nextPage() );
}