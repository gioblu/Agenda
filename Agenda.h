
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
