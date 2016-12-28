#include "DigiJoystick.h"

#define DAT 0
#define PS 1
#define CLK 2

#define PULSE_TIME 4

char buf[8] = {
  0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
  0x00, 0x00
};

void pulseClock(byte pin) {
  digitalWrite(pin, HIGH);
  delayMicroseconds(PULSE_TIME);
  digitalWrite(pin, LOW);
  delayMicroseconds(PULSE_TIME);
}

void setup() {
  pinMode(DAT, INPUT);
  pinMode(PS, OUTPUT);
  pinMode(CLK, OUTPUT);
  digitalWrite(PS, LOW);
  digitalWrite(CLK, LOW);
}

void loop() {
  buf[0] = buf[1] = 0x80;
  buf[6] = 0x00;
  pulseClock(CLK);
  pulseClock(PS);
  if (!digitalRead(DAT)) buf[6] |= 0x04;
  pulseClock(CLK);
  if (!digitalRead(DAT)) buf[6] |= 0x08;
  pulseClock(CLK);
  if (!digitalRead(DAT)) buf[6] |= 0x80;
  pulseClock(CLK);
  if (!digitalRead(DAT)) buf[6] |= 0x40;
  pulseClock(CLK);
  if (!digitalRead(DAT)) buf[1] -= 128;
  pulseClock(CLK);
  if (!digitalRead(DAT)) buf[1] += 127;
  pulseClock(CLK);
  if (!digitalRead(DAT)) buf[0] -= 128;
  pulseClock(CLK);
  if (!digitalRead(DAT)) buf[0] += 127;
  pulseClock(CLK);
  if (!digitalRead(DAT)) buf[6] |= 0x02;
  pulseClock(CLK);
  if (!digitalRead(DAT)) buf[6] |= 0x01;
  pulseClock(CLK);
  if (!digitalRead(DAT)) buf[6] |= 0x10;
  pulseClock(CLK);
  if (!digitalRead(DAT)) buf[6] |= 0x20;
  DigiJoystick.setValues(buf);
  DigiJoystick.update();
}
