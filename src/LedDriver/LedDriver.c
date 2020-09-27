#include "LedDriver.h"
#include "RuntimeError.h"

enum {ALL_LEDS_ON = ~0, ALL_LEDS_OFF = ~ALL_LEDS_ON};

static int16_t * ledsAddress;
static int16_t ledsImage;
void LedDriver_Create(uint16_t *leds) {

    ledsAddress = leds;
    ledsImage = 0;
    *ledsAddress = ledsImage;

}

static int16_t convertNumberToBits(int ledNumber) {
    return (1 << (ledNumber - 1));
}

void LedDriver_LedOn(int ledNumber) {
    if( ledNumber <= 0 || ledNumber > 16) {
        RUNTIME_ERROR("LedDriver : out-of-bound LED", -1);
        return;
    }

    ledsImage |= convertNumberToBits(ledNumber);
    *ledsAddress = ledsImage;
}

void LedDriver_LedOff(int ledNumber) {
    if( ledNumber <= 0 || ledNumber > 16) {
        RUNTIME_ERROR("LedDriver : out-of-bound LED", -1);
        return;
    }

    ledsImage &= ~convertNumberToBits(ledNumber);
    *ledsAddress = ledsImage;
}

void LedDriver_LedAllOn() {
    ledsImage = ALL_LEDS_ON;
    *ledsAddress = ledsImage;
}
