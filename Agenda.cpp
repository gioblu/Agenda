/* ___   ___   ___        __   ___
  |   | | __  |___ |\  | |  \ |   |
  |___| |   | |    | \ | |   ||___|
  |   | |___| |___ |  \| |__/ |   | version: 0.1

  Simple Scheduler library for Arduino
  Giovanni Blu Mitolo 2014 - gioscarab@gmail.com - www.gioblu.com
  This library has been released on the public domain.

  Agenda agenda;
  Define an instance of agenda (choose a name, agenda is only an example)

  agenda.insert(function (name with no brackets), interval in millis, once (true or false));
  Add the passed function in the tasks list, if once is true, task
  will be executed once. Returns a number (the id of the task)
  or -1 if is impossible to add the task.

  agenda.remove(id);
  Removes from tasks list the task that has the same id passed as parameter

  agenda.update();
  Checks all scheduled tasks and executes which has to be executed.

  agenda.delay(time);
  A delay function that avoid to affect the scheduler functionalities */

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

void Agenda::delay(unsigned long delay_time) {
  unsigned long time = micros();
  while(micros() - time > delay_time)
    this->update();
}
