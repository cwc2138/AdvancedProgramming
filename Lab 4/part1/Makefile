main: mdb.o
	gcc mdb.o -L./../../lab3/part1 -lmylist -o mdb-lookup
mdb.o: mdb.c mdb.h 
	gcc -c -Wall -g mdb.c -I./../../lab3/part1

.PHONY:clean
clean:
	rm -f *.o *~ a.out core mdb-lookup
