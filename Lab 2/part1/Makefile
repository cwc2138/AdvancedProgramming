main: main.o compareAsc.o compareDesc.o sort_integer_array.o
	gcc main.o compareAsc.o compareDesc.o sort_integer_array.o -o isort -g

main.o: main.c
	gcc -c -Wall -g main.c

compareAsc.o: compareAsc.c compareAsc.h
	gcc -c compareAsc.c

compareDesc.o: compareDesc.c compareDesc.h
	gcc -c compareDesc.c

sort_integer_array.o: sort_integer_array.c sort_integer_array.h
	gcc -c sort_integer_array.c

.PHONY: clean
clean:
	rm -f *.o *~ a.out core isort
