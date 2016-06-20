
/* ___   ___   ___        __   ___
  |   | | __  |___ |\  | |  \ |   |
  |___| |   | |    | \ | |   ||___|
  |   | |___| |___ |  \| |__/ |   | version: 1.0
  Scheduler library for Arduino
  Copyright (c) 2013-2016, Giovanni Blu Mitolo
  gioscarab@gmail.com - www.gioblu.com
  All rights reserved.
  
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */

#include "Agenda.h"

struct tasks_struct {
  void (*execution)(void);
  unsigned long timing;
  unsigned long registration;
  boolean active;
  boolean once;
  boolean empty;
};

tasks_struct _tasks[MAX_TASKS];

Agenda::Agenda() {
  for(int i = 0; i < MAX_TASKS; i++)
    _tasks[i].empty = true;
}

int Agenda::insert(void (*task)(void), unsigned long timing, boolean once) {
  for(byte i = 0; i < MAX_TASKS; i++)
    if(_tasks[i].empty) {
      _tasks[i].active = true;
      _tasks[i].execution = *task;
      _tasks[i].registration = micros();
      _tasks[i].timing = timing;
      _tasks[i].once = once;
      _tasks[i].empty = false;
      return i;
    }
  return -1;
}

void Agenda::activate(int id) {
  _tasks[id].active = true;
}

void Agenda::deactivate(int id) {
  _tasks[id].active = false;
}

void Agenda::remove(int id) {
  _tasks[id].active = NULL;
  _tasks[id].empty = true;
}

void Agenda::update() {
  // Save time once to reduce execution time
  unsigned long time = micros();
  for(byte i = 0; i < MAX_TASKS; i++)
    if(!_tasks[i].empty && _tasks[i].active)
      if(time - _tasks[i].registration > _tasks[i].timing) {
        _tasks[i].registration = time;
        _tasks[i].execution();
        if(_tasks[i].once)
          this->remove(i);
        time = micros();
        /* Bring time variable back coherent after
           task execution */
      }
}

void Agenda::delay(unsigned long delay) {
  unsigned long time = millis();
  while((unsigned long)(delay + time) > millis()) {
    this->update();
    yield();
  }
}

void Agenda::delay_microseconds(unsigned long delay) {
  unsigned long time = micros();
  while((unsigned long)(delay + time) > micros())  {
    this->update();
    yield();
  }
}
