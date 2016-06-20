Agenda 1.0 Stable
======

There are a lot of scheduler implementations for Arduino on github, I have developed Agenda because I needed an overflow proof implementation non interrupt-driven I could trust for HAB (High Altitude Balloon) launches and home automation experiments. Agenda is immune to `micros()` overflow and it is designed to work rock solid. The big PROs are the high resilience, compatibility with any sort of library and configurable memory consumption. Consider that Agenda, not using interrupts, can likely overshoot requested delays and scheduled executions with long duration tasks. 

I have developed the strong belief, after a lot of experience with Arduino compatible embedded systems, that is better to handle a possible delay in task execution (using a non interrupt-driven system like Agenda), than having always chances to get an interruption in the middle of an execution (using interrupt-driven software), that generally leads to execution corruption and unexpected bugs, for example in a strict timed scenario like bit-banging or sensor reading. 

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
  
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */
```
