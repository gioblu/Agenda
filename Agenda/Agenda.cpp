/*
  Agenda.cpp - Library for reflectometer sensor.
  Created by Giovanni Blu Mitolo, November 13, 2014.
  Released into the public domain.
*/

#include "WProgram.h"
#include "WConstants.h"
#include "Agenda.h"

Agenda::Agenda() {
}

void Agenda::insert(pointer_to_function task, int timing) {
  for(byte i = 0; i < 256; i++) 
    if(_tasks[i] == NULL) {
      _tasks[i] = task;
      _registrations[i] = millis();
      _timings[i] = timing;
    }
}

void Agenda::remove(int id) {
  _tasks[id] = NULL;
  _registrations[id] = NULL;
  _timings[id] = NULL;
}

void Agenda::update() {
  unsigned long time = millis();
  
  for(byte i = 0; i < 256; i++) 
    if(time - _registrations[i] > _timings[i]) {
      _tasks[i]();
      _registrations[i] = time;
    }
  
}
