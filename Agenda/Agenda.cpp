/*
  Agenda.cpp - Simple scheduler library.
  Created by Giovanni Blu Mitolo, November 13, 2014.
  Released into the public domain.
*/

#include "WProgram.h"
#include "WConstants.h"
#include "Agenda.h"

Agenda::Agenda() {

};

Agenda::add(void * task, int timing, byte priority) {
  for(byte i = 0; i < 256; i++)
    if(_tasks[i] == nullptr) {
    
      _tasks[i] = task;
      _registrations[i] = millis();
      _timings[i] = timing;
      _priorities[i] = priority;
      return i;

    } else if(i == 255) return NULL;
    

};

Agenda::remove(int id) {
  _tasks[id] = nullptr;
  _registrations[id] = 0;
  _timings[id] = 0;
  _priorities[id] = 0;
};

Agenda::check() {
  unsigned long time = millis();
  
  for(byte i = 0; i < 256; i++) 
    if(time - registrations[i] > _timings[i])
      _priorities[i] = 1;

  for(byte i = 0; i < 256; i++) {
    if(_priorities[i] == 1)
      _tasks[i]();
      _registrations[i] = time;
  }

  for(byte i = 0; i < 256; i++) 
      _priorities[i] = 0;

};

Agenda::taskList() {
  return _tasks;
};
