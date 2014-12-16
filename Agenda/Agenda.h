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

#ifndef Agenda_h
  #define Agenda_h

  #if defined(ARDUINO) && (ARDUINO >= 100)
    #include "Arduino.h"
  #else
    #include "WProgram.h"
    #include "WConstants.h"
  #endif
#endif

#define max_tasks 255
#define agenda_version 01

class Agenda {
  public:
    Agenda();
    int insert(void (*task)(void), unsigned long timing, boolean once = false);
    void remove(int id);
    void update();
    void delay(unsigned long delay_time);
  private:
};
