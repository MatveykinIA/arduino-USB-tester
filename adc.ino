// АЦП
// ADC

unsigned int _adcRAW1;
unsigned int _adcRAW2;
unsigned int _adcTime = 0;
float _adcA; // Current
float _adcV; // Voltage

float _adcRl;      // сопротивление нагрузки; load resistance
float _adcMWh = 0.0f; // миливатт  час; milliwatt hour

void adcSetup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  // встроенное опорное напряжение 1.1 В на микроконтроллерах ATmega168 и ATmega328, и 2.56 В на ATmega8.
  // built-in 1.1 V reference on ATmega168 and ATmega328 microcontrollers, and 2.56 V on ATmega8.
  analogReference(INTERNAL);
}

void adcLoop() {
  float f;

  _adcA = 0.0f;
  _adcV = 0.0f;
  for (int i = 0; i < 30; i++) {
    _adcRAW1 = analogRead(A0);
    Serial.print("A0: ");
    Serial.print(_adcRAW1);
    f = (float) _adcRAW1;
    _adcA += ((1.1f * f) / (1023.0f * configR1));
    _adcRAW2 = analogRead(A1);
    Serial.print("; A1: ");
    Serial.println(_adcRAW2);
    f = (float) _adcRAW2;
    _adcV += ((1.1f * f) / 1023.0f) * ((configR3 + configR5) / configR5);
    delay(10UL);
  }
  _adcA /= 30.0f;
  _adcV /= 30.0f;

  _adcRl = 0.0f;
  if (_adcA > configMinA) {
    _adcTime++;
    _adcRl = _adcV / _adcA - configR1;
    // 60 * 60 / 1000 = 3.6
    _adcMWh += (_adcA * _adcA * _adcRl) / 3.6f;
  }
  Serial.print("A:");
  Serial.print(_adcA);
  Serial.print("; V:");
  Serial.print(_adcV);
  Serial.print("; Time:");
  Serial.print(_adcTime);
  Serial.print("; Rl:");
  Serial.print(_adcRl);
  Serial.print("; mWh:");
  Serial.println(_adcMWh);
}

// RAW1
unsigned int adcRaw1() {
  return _adcRAW1;
}

// RAW2
unsigned int adcRaw2() {
  return _adcRAW2;
}

// Current
float adcA() {
  return _adcA;
}

// Voltage
float adcV() {
  return _adcV;
}

// Емкость
// Capacity mAh
float adcC() {
  return _adcMWh / configRatedVoltage;
}

float adcMWh() {
  return _adcMWh;
}

float adcRl() {
  return _adcRl;
}

unsigned int adcTime() {
  return _adcTime;
}
