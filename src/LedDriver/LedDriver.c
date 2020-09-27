#include "LedDriver.h"

static int16_t * ledsAddress;
void LedDriver_Create(uint16_t *leds) {

    ledsAddress = leds;
    *ledsAddress = 0;

}

void LedDriver_LedOn(int ledNumber) {

    *ledsAddress = 1;

}

void LedDriver_LedOff(int ledNumber) {

    *ledsAddress = 0;

}
