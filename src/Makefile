OBJECTS=main.o calendar.o io.o

CFLAGS=-Wall -ggdb `pkg-config --cflags --libs gtk+-2.0 libgcal glib-2.0 webkit-1.0 libxml-2.0 libxdg-basedir`

chronus: ${OBJECTS}
	${CC} -o ../chronus ${CFLAGS} ${OBJECTS}
