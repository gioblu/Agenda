
/* ___   ___   ___        __   ___
  |   | | __  |___ |\  | |  \ |   |
  |___| |   | |    | \ | |   ||___|
  |   | |___| |___ |  \| |__/ |   | version: 1.0
  Scheduler library for Arduino
  Copyright (c) 2013-2016, Giovanni Blu Mitolo
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
     "Timed by Agenda, developed by Giovanni Blu Mitolo"
  -  Neither the name of Agenda nor the
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

#ifndef Agenda_h
  #define Agenda_h

  #if defined(ARDUINO) && (ARDUINO >= 100)
    #include "Arduino.h"
  #else
    #include "WProgram.h"
    #include "WConstants.h"
  #endif
#endif

#define MAX_TASKS 20

class Agenda {
  public:
    Agenda();
    int insert(void (*task)(void), unsigned long timing, boolean once = false);
    void remove(int id);
    void activate(int id);
    void deactivate(int id);
    void update();
    void delay(unsigned long delay);
    void delay_microseconds(unsigned long delay);
  private:
};
