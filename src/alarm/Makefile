DEMO_BIN=alarm_demo
DEMO_SRC=demo.cpp alarm.cpp

CPPFLAGS=-std=c++11 -ggdb
VSQLITEFLAGS=-lvsqlitepp

.PHONY: all clean

all: ${DEMO_BIN}

${DEMO_BIN}: $(DEMO_SRC:.cpp=.o)
	g++ $^ -o $@ ${VSQLITEFLAGS} `pkg-config sigc++-2.0 --libs`

%.o: %.cpp
	g++ -c ${CPPFLAGS} $< -o $@ `pkg-config sigc++-2.0 --cflags`

clean:
	rm -f ${TARGET}
