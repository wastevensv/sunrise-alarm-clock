SUNRISE_BIN=sunrise
SUNRISE_SRC=sunrise.cpp display/display.cpp alarm/alarm.cpp

MKALARM_BIN=mkalarm
MKALARM_SRC=mkalarm.cpp alarm/alarm.cpp arg_parser.hpp

CPPFLAGS=-std=c++11 -ggdb
VSQLITEFLAGS=-lvsqlitepp

.PHONY: all clean

all: ${SUNRISE_BIN} ${MKALARM_BIN}

${SUNRISE_BIN}: $(SUNRISE_SRC:.cpp=.o)
	g++ $^ -o $@ ${VSQLITEFLAGS} `pkg-config gtkmm-3.0 --libs`

${MKALARM_BIN}: $(MKALARM_SRC:.cpp=.o)
	g++ $^ -o $@ ${VSQLITEFLAGS} `pkg-config sigc++-2.0 --libs`

%.o: %.cpp
	g++ -c ${CPPFLAGS} $< -o $@ `pkg-config gtkmm-3.0 --cflags` `pkg-config sigc++-2.0 --cflags`

clean:
	rm -f ${SUNRISE_BIN} ${MKALARM_BIN}
