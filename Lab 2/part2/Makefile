main: twecho.o
	gcc twecho.o -o twecho -g
twecho.o: twecho.c
	gcc -c -Wall -g twecho.c

.PHONY: clean
clean:
	rm -f *.o *~ a.out core twecho
