#include "unity_fixture.h"


TEST_GROUP_RUNNER(LedDriver)
{
    RUN_TEST_CASE(LedDriver, LedsOffAfterCreate);
    RUN_TEST_CASE(LedDriver, LedSwitchOn);
    RUN_TEST_CASE(LedDriver, LedSwitchOff);
}
