http-server: http-server.o
	gcc http-server.o -g -o http-server
http-server.o: http-server.c
	gcc -c -Wall -g http-server.c

.PHONY:clean
clean:
	rm -f *.o *~ a.out core http-server
