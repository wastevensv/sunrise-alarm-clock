TARGET=sunrise
SOURCES=main.cpp display/display.cpp

all: ${TARGET}

${TARGET}: ${SOURCES}
	g++ ${SOURCES} -o ${TARGET} `pkg-config gtkmm-3.0 --cflags --libs`

clean:
	rm -f ${TARGET}
