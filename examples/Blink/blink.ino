#include <Agenda.h>

Agenda scheduler;

void setup() {
  pinMode(13, OUTPUT);
  scheduler.insert(blink, 1000000);
}

void blink() {
  digitalWrite(13, HIGH);
  delay(10);
  digitalWrite(13, LOW);
}

void loop() {
  scheduler.update();
};
