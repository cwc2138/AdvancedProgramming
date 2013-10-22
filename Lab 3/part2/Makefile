main: revecho.o 
	gcc revecho.o -L./../part1 -lmylist -o revecho
revecho.o: revecho.c
	gcc -c -Wall -g revecho.c -I./../part1

PHONY: clean
clean:
	rm -f *.o *~a.out core revecho
