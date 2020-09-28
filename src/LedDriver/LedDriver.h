#include <stdint.h>

#define FALSE 0
#define TRUE  1
typedef int BOOL;

void LedDriver_Create(uint16_t *leds);
void LedDriver_LedOn(int ledNumber);
void LedDriver_LedOff(int ledNumber);
void LedDriver_LedAllOn();
void LedDriver_LedAllOff();
BOOL LedDriver_IsOn(int ledNumber);
BOOL LedDriver_IsOff(int ledNumber);
