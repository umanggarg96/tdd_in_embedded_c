#include "unity_fixture.h"
#include "LedDriver.h"
#include "RuntimeErrorStub.h"

TEST_GROUP(LedDriver);

static uint16_t leds;

static void corruptLeds(uint16_t newLeds) {
    leds = newLeds;
}

TEST_SETUP(LedDriver) {
    LedDriver_Create(&leds);
}

TEST_TEAR_DOWN(LedDriver) {
    RuntimeErrorStub_Reset();

}

TEST(LedDriver, LedsOffAfterCreate) {
    uint16_t leds = 0xffff;
    LedDriver_Create(&leds);
    TEST_ASSERT_EQUAL_HEX16(0, leds);
}

TEST(LedDriver, LedSwitchOn) {
    LedDriver_LedOn(1);
    TEST_ASSERT_EQUAL_HEX16(1, leds);
}

TEST(LedDriver, LedSwitchOff) {
    LedDriver_LedOn(1);
    LedDriver_LedOff(1);
    TEST_ASSERT_EQUAL_HEX16(0, leds);
}

TEST(LedDriver, LedSwitchOnMultiple) {
    LedDriver_LedOn(8);
    LedDriver_LedOn(9);
    TEST_ASSERT_EQUAL_HEX16(0x0180, leds);
}

TEST(LedDriver, LedSwitchOffMultiple) {
    LedDriver_LedOn(8);
    LedDriver_LedOn(9);
    LedDriver_LedOff(8);
    LedDriver_LedOff(9);
    TEST_ASSERT_EQUAL_HEX16(0, leds);
}

TEST(LedDriver, LedSwitchOffSingle) {
    LedDriver_LedAllOn();;
    LedDriver_LedOff(8);
    TEST_ASSERT_EQUAL_HEX16(0xff7f, leds);
}

TEST(LedDriver, LedTurnAllOn) {
    LedDriver_LedAllOn();
    TEST_ASSERT_EQUAL_HEX16(0xffff, leds);
}

TEST(LedDriver, LedIsNotReadable) {
    corruptLeds(0xffff);
    LedDriver_LedOn(8);
    TEST_ASSERT_EQUAL_HEX16(0x0080, leds);
}

TEST(LedDriver, UpperAndLowerBoundsOn) {
    LedDriver_LedOn(1);
    LedDriver_LedOn(16);
    TEST_ASSERT_EQUAL_HEX16(0x8001, leds);
}

TEST(LedDriver, UpperAndLowerBoundsOff) {
    LedDriver_LedAllOn();
    LedDriver_LedOff(1);
    LedDriver_LedOff(16);
    TEST_ASSERT_EQUAL_HEX16(0x7FFE, leds);
}

TEST(LedDriver, OutOfBoundsOn) {
    LedDriver_LedOn(-1);
    LedDriver_LedOn(0);
    LedDriver_LedOn(17);
    LedDriver_LedOn(3141);
    TEST_ASSERT_EQUAL_HEX16(0x0000, leds);
}

TEST(LedDriver, OutOfBoundsOff) {
    LedDriver_LedAllOn();
    LedDriver_LedOff(-1);
    LedDriver_LedOff(0);
    LedDriver_LedOff(17);
    LedDriver_LedOff(3141);
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, leds);
}


TEST(LedDriver, OutOfBoundTurnOnProdceRuntimeError) {
    LedDriver_LedOn(-1);
    TEST_ASSERT_EQUAL_STRING("LedDriver : out-of-bound LED", 
                   RuntimeErrorStub_GetLastError());
    TEST_ASSERT_EQUAL(-1, RuntimeErrorStub_GetLastParameter());
}


TEST(LedDriver, OutOfBoundTurnOffProdceRuntimeError) {
    LedDriver_LedOff(-1);
    TEST_ASSERT_EQUAL_STRING("LedDriver : out-of-bound LED", 
                   RuntimeErrorStub_GetLastError());
    TEST_ASSERT_EQUAL(-1, RuntimeErrorStub_GetLastParameter());
}

TEST(LedDriver, IsOn) {
    TEST_ASSERT_FALSE(LedDriver_IsOn(1));
    LedDriver_LedOn(1);
    TEST_ASSERT_TRUE(LedDriver_IsOn(1));
}

TEST(LedDriver, UpperAndLowerBoundsIsOn) {
    TEST_ASSERT_FALSE(LedDriver_IsOn(1));
    TEST_ASSERT_FALSE(LedDriver_IsOn(16));
    LedDriver_LedOn(1);
    LedDriver_LedOn(16);
    TEST_ASSERT_TRUE(LedDriver_IsOn(1));
    TEST_ASSERT_TRUE(LedDriver_IsOn(16));
}

TEST(LedDriver, OutOfBoundIsOnReturnsFalse) {
    LedDriver_LedAllOn();
    TEST_ASSERT_FALSE(LedDriver_IsOn(-1));
    TEST_ASSERT_FALSE(LedDriver_IsOn(17));
    TEST_ASSERT_FALSE(LedDriver_IsOn(0));
    TEST_ASSERT_FALSE(LedDriver_IsOn(3141)); 
}

TEST(LedDriver, OutOfBoundIsOnProducesRuntimeError) {
    TEST_ASSERT_FALSE(LedDriver_IsOn(17));
    TEST_ASSERT_EQUAL_STRING("LedDriver : out-of-bound LED", 
                   RuntimeErrorStub_GetLastError());
    TEST_ASSERT_EQUAL(-1, RuntimeErrorStub_GetLastParameter());
}

TEST(LedDriver, LedTurnAllOff)
{
    LedDriver_LedAllOn();
    LedDriver_LedAllOff();
    TEST_ASSERT_EQUAL_HEX16(0x0000, leds);
}

TEST(LedDriver, IsOff)
{
    LedDriver_LedAllOn();
    TEST_ASSERT_FALSE(LedDriver_IsOff(1));
    LedDriver_LedOff(1);
    TEST_ASSERT_TRUE(LedDriver_IsOff(1));
}

TEST(LedDriver, OutOfBoundIsOffReturnsTrue) {
    LedDriver_LedAllOn();
    TEST_ASSERT_TRUE(LedDriver_IsOff(-1));
    TEST_ASSERT_TRUE(LedDriver_IsOff(17));
    TEST_ASSERT_TRUE(LedDriver_IsOff(0));
    TEST_ASSERT_TRUE(LedDriver_IsOff(3141)); 
}
