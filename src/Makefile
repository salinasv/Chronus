OBJECTS=main.o google.o

CFLAGS=-Wall -ggdb `pkg-config --cflags --libs gtk+-2.0 libgcal`

chronus: ${OBJECTS}
	${CC} -o ../chronus ${CFLAGS} ${OBJECTS}
