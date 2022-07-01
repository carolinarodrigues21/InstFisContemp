#include "Volume.h" // Include the Volume library

// speaker connected to digital pin 5

Volume vol; // Plug your speaker into the default pin for your board type:
// https://github.com/connornishijima/arduino-volume1#supported-pins

void setup() {
  vol.begin();
}
void loop() {
  byte volumes[4] = {255, 127, 12, 0};   // List of volumes: 100% Volume, 50% Volume, 5% Volume, 0% Volume
  for (int i = 0; i < 4; i++) { // Iterate through volume list one second at a time
    vol.tone(440, volumes[i]);
    vol.delay(1000);
  }
}
