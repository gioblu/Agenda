Agenda 1.0 Stable
======

There are a lot of scheduler implementations for Arduino on github, I have developed Agenda because I needed an overflow proof implementation non interrupt-driven I could trust for HAB (High Altitude Balloon) launches and home automation experiments. Agenda is immune to `micros()` overflow and it is designed to work rock solid. The big PROs are the high resilience, compatibility with any sort of library and configurable memory consumption. Consider that Agenda, not using interrupts, can likely overshoot requested delays and scheduled executions with long duration tasks. 

I have developed a strong belief, after a lot of experience with Arduino compatible embedded systems, that is better to handle a possible delay in task execution (using a non interrupt-driven system like Agenda), than having always chances to get an interruption in the middle of an execution, that generally leads to execution corruption and unexpected bugs, for example in a strict timed scenario like bit-banging or sensor reading task. 

First you have to instantiate the Agenda object:
```cpp
Agenda scheduler;
```

Call update method at least one per loop cycle:
```cpp
scheduler.update();
```

To add a function execution to the list of scheduled tasks:
```cpp
// Function definition
void blink() {
  Serial.println("Blink!");
}

int blink = scheduler.insert(blink, 1000000); // Blink every second 
```

If you want to execute the task only once pass `true` as third parameter:
```cpp
int blink = scheduler.insert(blink, 1000000, true);
```

If you want to deactivate the task you added:
```cpp
scheduler.deactivate(blink);
```

If you want to activate the task:
```cpp
scheduler.activate(blink);
```

If you want to completely remove it:
```cpp
scheduler.remove(blink);
```

If you need a delay in your code use these functions:
```cpp
// Delay of 1 second while executing tasks when necessary
scheduler.delay(1000); 

// Delay of 100 microseconds while executing tasks when necessary
scheduler.delay_microseconds(100); 
```

##License
```cpp
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
```
