main: mylist-test.o mylist.o libmylist.a
	gcc -g mylist-test.o mylist.o libmylist.a -o mylist-test 
libmylist.a: mylist.o
	ar rc libmylist.a  mylist.o
	ranlib libmylist.a
mylist-test.o: mylist-test.c mylist.h
	gcc -c -Wall -g mylist-test.c
mylist.o: mylist.c mylist.h
	gcc -c -Wall -g mylist.c

PHONY: clean
clean:
	rm -f *.a *.o *~a.out core mylist-test
