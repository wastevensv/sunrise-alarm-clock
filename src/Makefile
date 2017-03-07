TARGET=sunrise
SOURCES=main.cpp display/display.cpp alarm/alarm_mgr.cpp
CPPFLAGS=-std=c++11 -ggdb
VSQLITEFLAGS=-lvsqlitepp

all: ${TARGET}

${TARGET}: ${SOURCES}
	g++ ${CPPFLAGS} ${SOURCES} -o ${TARGET} `pkg-config gtkmm-3.0 --cflags --libs` ${VSQLITEFLAGS}

clean:
	rm -f ${TARGET}
