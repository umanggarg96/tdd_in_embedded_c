#include "LedDriver.h"
#include "RuntimeError.h"

enum {ALL_LEDS_ON = ~0, ALL_LEDS_OFF = ~ALL_LEDS_ON};
enum {UPPER_LED   = 16, LOWER_LED = 1};

static int16_t * ledsAddress;
static int16_t ledsImage;

static int16_t convertNumberToBits(int ledNumber) {
    return (1 << (ledNumber - 1));
}

static void updateHardware() {
    *ledsAddress = ledsImage;
}

static BOOL isLedOutOfBounds(int ledNumber)
{
    return (ledNumber < LOWER_LED || ledNumber > UPPER_LED);
}
void LedDriver_Create(uint16_t *leds) {

    ledsAddress = leds;
    ledsImage = ALL_LEDS_OFF;
    updateHardware();
}

void LedDriver_LedOn(int ledNumber) {
    if(isLedOutOfBounds(ledNumber)) {
        RUNTIME_ERROR("LedDriver : out-of-bound LED", -1);
        return;
    }

    ledsImage |= convertNumberToBits(ledNumber);
    updateHardware();
}

void LedDriver_LedOff(int ledNumber) {
    if(isLedOutOfBounds(ledNumber)) {
        RUNTIME_ERROR("LedDriver : out-of-bound LED", -1);
        return;
    }

    ledsImage &= ~convertNumberToBits(ledNumber);
    updateHardware();
}

void LedDriver_LedAllOn() {
    ledsImage = ALL_LEDS_ON;
    updateHardware();
}

void LedDriver_LedAllOff() {
    ledsImage = ALL_LEDS_OFF;
    updateHardware();
}

BOOL  LedDriver_IsOn(int ledNumber) {
    if(isLedOutOfBounds(ledNumber)) {
        RUNTIME_ERROR("LedDriver : out-of-bound LED", -1);
        return FALSE;
    }
    return ledsImage & convertNumberToBits(ledNumber);
}

BOOL  LedDriver_IsOff(int ledNumber) {
    return !LedDriver_IsOn(ledNumber);
}
