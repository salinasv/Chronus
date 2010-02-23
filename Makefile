OBJECTS=main.o

CFLAGS=-Wall -ggdb `pkg-config --cflags --libs gtk+-2.0`

chronus: ${OBJECTS}
	${CC} -o chronus ${CFLAGS} ${OBJECTS}
