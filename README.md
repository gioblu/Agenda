Agenda
======

There are a lot of scheduler implementations for Arduino on github, I have developed Cape because I needed an overflow proof implementation I could trust for HAB (High Altitude Balloon) launches and home automation experiments. Agenda is immune to `millis()` overflow and it is designed to work rock solid.

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

int blink = scheduler.insert(blink, 1000);
```

If you want to deactivate the task you added:
```cpp
scheduler.deactivate(blink);
```

To activate:
```cpp
scheduler.activate(blink);
```

If you want to completely remove it:
```cpp
scheduler.remove(blink);
```

---

Copyright (c) 2013-2015, Giovanni Blu Mitolo
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
   This product includes software developed by the <organization>.

-  Neither the name of the <organization> nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

This software is provided by the copyright holders and contributors "as is" and any express or implied warranties, including, but not limited to, the implied warranties of merchantability and fitness for a particular purpose are disclaimed. In no event shall the copyright holder or contributors be liable for any direct, indirect, incidental, special, exemplary, or consequential damages (including, but not limited to, procurement of substitute goods or services; loss of use, data, or profits; or business interruption) however caused and on any theory of liability, whether in contract, strict liability, or tort (including negligence or otherwise) arising in any way out of the use of this software, even if advised of the possibility of such damage.
