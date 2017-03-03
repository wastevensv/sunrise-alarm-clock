TARGET=alarm_demo
SOURCES=demo.cpp alarm_mgr.cpp
CPPFLAGS=-std=c++11

all: ${TARGET}

${TARGET}: ${SOURCES}
	g++ ${CPPFLAGS} ${SOURCES} -o ${TARGET} `pkg-config gtkmm-3.0 --cflags --libs`

clean:
	rm -f ${TARGET}
