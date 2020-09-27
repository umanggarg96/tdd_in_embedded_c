
UNITY_ROOT=/home/umang96/work/repos/Unity

INC=-I../src/LedDriver -I${UNITY_ROOT}/src -I${UNITY_ROOT}/extras/fixture/src  -I${UNITY_ROOT}/extras/memory/src
UNITY=${UNITY_ROOT}/src/unity.c ${UNITY_ROOT}/extras/fixture/src/unity_fixture.c
SRC=../src/LedDriver/*.c
TEST=LedDriver/*.c AllTests.c 

all: compile
	./test

compile:
	gcc  $(INC) $(UNITY) $(SRC) $(TEST) -o test

clean:
	rm -rf test
