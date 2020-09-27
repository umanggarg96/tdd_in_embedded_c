#include "unity_fixture.h"


TEST_GROUP_RUNNER(LedDriver)
{
    RUN_TEST_CASE(LedDriver, LedsOffAfterCreate);
    RUN_TEST_CASE(LedDriver, LedSwitchOn);
    RUN_TEST_CASE(LedDriver, LedSwitchOff);
    RUN_TEST_CASE(LedDriver, LedSwitchOnMultiple);
    RUN_TEST_CASE(LedDriver, LedSwitchOffMultiple);
    RUN_TEST_CASE(LedDriver, LedSwitchOffSingle);
    RUN_TEST_CASE(LedDriver, LedTurnAllOn);
    RUN_TEST_CASE(LedDriver, LedIsNotReadable);
    RUN_TEST_CASE(LedDriver, UpperAndLowerBoundsOn);
    RUN_TEST_CASE(LedDriver, OutOfBoundsOn);
    RUN_TEST_CASE(LedDriver, UpperAndLowerBoundsOff);
    RUN_TEST_CASE(LedDriver, OutOfBoundsOff);
    RUN_TEST_CASE(LedDriver, OutOfBoundTurnOnProdceRuntimeError);
    RUN_TEST_CASE(LedDriver, OutOfBoundTurnOffProdceRuntimeError);
}
