#include "unity_fixture.h"
#include "LedDriver.h"

TEST_GROUP(LedDriver);

TEST_SETUP(LedDriver) {

}

TEST_TEAR_DOWN(LedDriver) {


}

TEST(LedDriver, LedsOffAfterCreate) {
    int16_t leds = 0xffff;
    LedDriver_Create(&leds);
    TEST_ASSERT_EQUAL_HEX16(0, leds);
}

TEST(LedDriver, LedSwitchOn) {
    int16_t leds = 0xffff;
    LedDriver_Create(&leds);
    LedDriver_LedOn(1);
    TEST_ASSERT_EQUAL_HEX16(1, leds);
}

TEST(LedDriver, LedSwitchOff) {
    int16_t leds = 0xffff;
    LedDriver_Create(&leds);
    LedDriver_LedOn(1);
    LedDriver_LedOff(1);
    TEST_ASSERT_EQUAL_HEX16(0, leds);
}
