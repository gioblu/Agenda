
/* ___   ___   ___        __   ___
  |   | | __  |___ |\  | |  \ |   |
  |___| |   | |    | \ | |   ||___|
  |   | |___| |___ |  \| |__/ |   | version: 0.1

  Simple Scheduler library for Arduino
  Copyright (c) 2013-2015, Giovanni Blu Mitolo 2014
  gioscarab@gmail.com - www.gioblu.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.

  -  Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.

  -  All advertising materials mentioning features or use of this software
     must display the following acknowledgement:
     This product includes Agenda developed by Giovanni Blu Mitolo.

  -  Neither the name of Giovanni Blu Mitolo nor the
     names of its contributors may be used to endorse or promote products
     derived from this software without specific prior written permission.

  This software is provided by the copyright holders and contributors "as is"
  and any express or implied warranties, including, but not limited to, the
  implied warranties of merchantability and fitness for a particular purpose
  are disclaimed. In no event shall the copyright holder or contributors be
  liable for any direct, indirect, incidental, special, exemplary, or
  consequential damages (including, but not limited to, procurement of
  substitute goods or services; loss of use, data, or profits; or business
  interruption) however caused and on any theory of liability, whether in
  contract, strict liability, or tort (including negligence or otherwise)
  arising in any way out of the use of this software, even if advised of
  the possibility of such damage. */

#include "Agenda.h"

struct tasks_struct {
  void (*execution)(void);
  unsigned long timing;
  unsigned long registration;
  boolean active;
  boolean once;
  boolean empty;
};

tasks_struct _tasks[max_tasks];

Agenda::Agenda() {
  for(int i = 0; i < max_tasks; i++)
    _tasks[i].empty = true;
}

int Agenda::insert(void (*task)(void), unsigned long timing, boolean once) {
  for(byte i = 0; i < max_tasks; i++)
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
  unsigned long time = micros();
  for(byte i = 0; i < max_tasks; i++)
    if(!_tasks[i].empty && _tasks[i].active)
      if(time - _tasks[i].registration > _tasks[i].timing) {
        _tasks[i].execution();
        _tasks[i].registration = time;
        if(_tasks[i].once)
          this->remove(i);
      }
}

void Agenda::delay(unsigned long delay) {
  unsigned long time = millis();
  // Freek condition used to avoid millis() overflow
  while(!((unsigned long)(millis() - time) > delay)) {
    this->update();
    yield();
  }
}

void Agenda::delay_microseconds(unsigned long delay) {
  unsigned long time = micros();
  // Freek condition used to avoid micros() overflow
  while(!((unsigned long)(micros() - time) > delay))  {
    this->update();
    yield();
  }
}
