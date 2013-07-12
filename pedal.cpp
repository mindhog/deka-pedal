// Copyright 2013 Google Inc.  All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <WProgram.h>

const int bottomPin = 2;  // start at pin 2, 0 & 1 are receive and xmit
const int bounceDelay = 50;

bool state[bottomPin + 10];
long lastEventTime[bottomPin + 10];

void setup(void) {
    Serial.begin(115200);   // We'll send debugging information via the Serial monitor
    for (int i = bottomPin; i < bottomPin + 10; ++i) {
        pinMode(i, INPUT);
        
        // doing this on an input port turns on the pull-down resistor to 
        // reduce the sensitivity of the input.
        digitalWrite(i, HIGH);

        lastEventTime[i] = 0;        
        state[i] = false;
    }
}

void loop(void) {
    for (int i = bottomPin; i < bottomPin + 10; ++i) {
        int pressed = !digitalRead(i);
        long time = millis();
        
        if (pressed != state[i] && time - lastEventTime[i] > bounceDelay) {
            state[i] = pressed;
            lastEventTime[i] = time;
            if (pressed)
                Serial.write(i - bottomPin);
            else
                Serial.write(128 | (i - bottomPin));
        }
    }
}
