OBJECTS=calendar.o io.o caldav.o

CFLAGS=-Wall -ggdb `pkg-config --cflags --libs gtk+-2.0 libgcal glib-2.0 webkit-1.0 libxml-2.0 libxdg-basedir libcaldav` -lcaldav

all: ../chronus ../test.bin

clean:
	rm *.o

../chronus: ${OBJECTS} main.c
	${CC} -o ../chronus ${CFLAGS} ${OBJECTS} main.c

../test.bin: ${OBJECTS} test.c
	${CC} -o ../test.bin ${CFLAGS} ${OBJECTS} test.c

