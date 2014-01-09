.PHONY: default
default: mdb-lookup-server-nc-2 mdb-lookup-server-nc-1
mdb-lookup-server-nc-1: mdb-lookup-server-nc-1.o
	gcc mdb-lookup-server-nc-1.o -g -o mdb-lookup-server-nc-1
mdb-lookup-server-nc-1.o: mdb-lookup-server-nc-1.c
	gcc -c -g -Wall mdb-lookup-server-nc-1.c
mdb-lookup-server-nc-2: mdb-lookup-server-nc-2.o
	gcc mdb-lookup-server-nc-2.o -g -o mdb-lookup-server-nc-2
mdb-lookup-server-nc-2.o: mdb-lookup-server-nc-2.c
	gcc -c -g -Wall mdb-lookup-server-nc-2.c

.PHONY: clean
clean:
	rm -f *.o mypipe-* *~a.out core mdb-lookup-server-nc-1 mdb-lookup-server-nc-2
