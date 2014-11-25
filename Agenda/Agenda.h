/*
  Agenda.h - Library for reflectometer sensor.
  Created by Giovanni Blu Mitolo, November 13, 2014.
  Released into the public domain.
*/

#ifndef Agenda_h
#define Agenda_h
#include "WProgram.h"
#include "WConstants.h"
#endif


typedef void (*pointer_to_function)(); // pointer to function with no args and void return

class Agenda {

  public:

    Agenda();
    
    void insert(pointer_to_function task, int timing);
    void remove(int id);
    void update();

  private:

    pointer_to_function _tasks[255];
    int  _timings[255];
    unsigned long _registrations[255];

};
