all:
	make -C src

test:
	./test.bin

clean:
	rm chronus
	rm test.bin
	make -C src clean
