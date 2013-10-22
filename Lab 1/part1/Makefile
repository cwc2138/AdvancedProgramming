main: main.o gcd.o prime.o
	gcc main.o gcd.o prime.o -o main -lm -g
main.o: main.c prime.h gcd.h
	gcc -c -Wall -g main.c
prime.o: prime.c prime.h
	gcc -c -Wall -g prime.c
gcd.o: gcd.c gcd.h
	gcc -c -Wall -g gcd.c

.PHONY: clean
clean:
		rm -f *.o *~a.out core main
