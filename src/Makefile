CXX?=g++
SUNRISE_BIN=sunrise
SUNRISE_SRC=sunrise.cpp display/display.cpp alarm/alarm.cpp

MKALARM_BIN=mkalarm
MKALARM_SRC=mkalarm.cpp alarm/alarm.cpp arg_parser.hpp

CPPFLAGS=-std=c++11 -ggdb
VSQLITEFLAGS=-lvsqlitepp

.PHONY: all clean clean-all

all: ${SUNRISE_BIN} ${MKALARM_BIN}

${SUNRISE_BIN}: $(SUNRISE_SRC:.cpp=.o)
	${CXX} $^ -o $@ ${VSQLITEFLAGS} `pkg-config gtkmm-3.0 --libs`

${MKALARM_BIN}: $(MKALARM_SRC:.cpp=.o)
	${CXX} $^ -o $@ ${VSQLITEFLAGS} `pkg-config sigc++-2.0 --libs`

%.o: %.cpp
	${CXX} -c ${CPPFLAGS} $< -o $@ `pkg-config gtkmm-3.0 --cflags`

clean:
	find . -iname "*.o" -delete

clean-all: clean
	rm -f ${SUNRISE_BIN} ${MKALARM_BIN}
