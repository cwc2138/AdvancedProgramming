main: main.o
	gcc main.o -o convert

main.o: main.c
	gcc -c -Wall -g main.c

.PHONY: clean
clean:
	rm -f *.o *~ a.out core convert
