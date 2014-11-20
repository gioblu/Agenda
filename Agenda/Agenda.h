/*
  Agenda.h - Simple scheduler library.
  Created by Giovanni Blu Mitolo, November 13, 2014.
  Released into the public domain.
*/

#ifndef Agenda_h
#define Agenda_h
#include "WProgram.h"
#include "WConstants.h"
#endif

class Agenda {

  public:

    void Agenda();
    
    byte add();
    void remove();
    void check();
    void tasksList();

  private:

    void _tasks[255];
    int  _timings[255];
    unsigned long _registrations[255]
    byte _executions[255];
    byte _priorities[255];

};
