#include "DigiJoystick.h"

#define DAT 0
#define PS 1
#define CLK 2

void pulseClock(byte pin) {
  digitalWrite(pin, HIGH);
  asm volatile ("nop\n\t");
  digitalWrite(pin, LOW);
  asm volatile ("nop\n\t");
}

void setup() {
  pinMode(DAT, INPUT);
  pinMode(PS, OUTPUT);
  pinMode(CLK, OUTPUT);
  digitalWrite(PS, LOW);
  digitalWrite(CLK, LOW);
}

void loop() {
  char buf[8] = {
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x00, 0x00
  };
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
