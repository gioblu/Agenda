/* ___   ___   ___        __   ___
  |   | | __  |___ |\  | |  \ |   |
  |___| |   | |    | \ | |   ||___|
  |   | |___| |___ |  \| |__/ |   | version: 0.1

  Simple Scheduler library for Arduino
  Giovanni Blu Mitolo 2014 - gioscarab@gmail.com - www.gioblu.com
  This library has been released on the public domain.

  Agenda agenda;
  Define an instance of agenda (choose a name, agenda is only an example)

  agenda.insert(function, interval in milliseconds);
  Add the passed function in the tasks list. Returns a number
  (the id of the task) or 0 if is impossible to add the task.

  agenda.remove(id);
  Removes the task from the tasks list that has the same id passed as parameter

  agenda.update();
  Checks all scheduled tasks and executes which has to be executed. */

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

Agenda::Agenda(char *time_measure) {
  if(time_measure == 'microseconds') _time_measure = 'u';
  if(time_measure == 'milliseconds') _time_measure = 'm';
  if(time_measure == 'seconds') _time_measure = 's';
}

unsigned long Agenda::calculate_time() {
  if(_time_measure == 'u') return micros();
  if(_time_measure == 'm') return millis();
  if(_time_measure == 's') return millis() / 1000;
}

int Agenda::insert(void (*task)(void), unsigned long timing, boolean once) {
  for(byte i = 0; i < max_tasks; i++)
    if(_tasks[i] == NULL) {
      _tasks[i].active = true;
      _tasks[i].execution = *task;
      _tasks[i].registration = calculate_time();
      _tasks[i].timing = timing;
      _tasks[i].once = once;
      return i;
    }
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
  unsigned long time = calculate_time();
  for(byte i = 0; i < max_tasks; i++)
    if((time - tasks[i].registration > _tasks[i].timing) && _tasks[i].active) {
      _tasks[i].execution();
      _tasks[i].registration = time;
    }
}

void Agenda::delay(unsigned long delay_time) {
  unsigned long time = calculate_time();
  while(calculate_time() - time < delay_time)
    this->update();
}
