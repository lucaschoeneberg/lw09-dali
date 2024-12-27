# LED-Warrior 09

This library provides an interface for managing DALI-compatible lighting systems through an I²C bus. It relies on the Wire library for all low-level I²C operations and exposes functions for sending DALI commands, reading status flags, querying device data, and configuring switch inputs. It defines classes that help organize the communication routines, so users can address DALI lights, adjust brightness levels, and perform basic device configuration without dealing directly with register-level details.

```cpp
#include <Wire.h>
#include "LW09_Dali.h"

LW09Dali daliModule(0x29);

void setup() {
  Wire.begin();
  // Set lamp with short address 1 to half brightness.
  daliModule.setLampLevel(1, 128);
}

void loop() {
  // Main application code.
}
```

For further details, refer to the comments in the header file, which explain each function, its parameters, and the expected address ranges.
