/* ___   ___   ___        __   ___
  |   | | __  |___ |\  | |  \ |   |
  |___| |   | |    | \ | |   ||___|
  |   | |___| |___ |  \| |__/ |   | version: 0.1

  Simple Scheduler library for Arduino
  Giovanni Blu Mitolo 2014 - gioscarab@gmail.com - www.gioblu.com
  This library has been released on the public domain.

  Agenda agenda((micros, millis or seconds with no brackets and no quotes) time_measure);
  Define an instance of agenda (choose a name, agenda is only an example)
  and pass a time measure: seconds, millis or micros

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

#include "WProgram.h"
#include "WConstants.h"
#include "Agenda.h"

struct tasks_struct {
	void (*execution)(void);
	unsigned long timing;
	unsigned long registration;
  boolean active;
  boolean execute_once;
};

tasks_struct _tasks[max_tasks];

unsigned long seconds() {
  return millis() / 1000;
}

Agenda::Agenda(unsigned long (*time_measure)(void) ) {
  _time_measure = &time_measure;
}

int Agenda::insert(void (*task)(void), unsigned long timing, boolean once) {
  for(byte i = 0; i < max_tasks; i++)
    if(_tasks[i] == NULL) {
      _tasks[i].active = true;
      _tasks[i].execution = *task;
      _tasks[i].registration = (*_time_measure)();
      _tasks[i].timing = timing;
      _tasks[i].once = once;
      return i;
    }

  return -1;
}

void Agenda::activate(int id) {
  _tasks[i].active = true;
}

void Agenda::deactivate(int id) {
  _tasks[i].active = false;
}

void Agenda::remove(int id) {
  _tasks[i].active = NULL;
  _tasks[i].execution = NULL;
  _tasks[i].registration = NULL;
  _tasks[i].timing = NULL;
  _tasks[i].once = NULL;
}

void Agenda::update() {
  unsigned long time = (*_time_measure)();
  for(byte i = 0; i < max_tasks; i++)
    if((time - tasks[i].registration > _tasks[i].timing) && _tasks[i].active) {
      _tasks[i].execution();
      _tasks[i].registration = time;
    }
}

void Agenda::delay(unsigned long delay_time) {
  unsigned long time = (*_time_measure)();
  while((*_time_measure)() - time > delay_time)
    this->update();
}
