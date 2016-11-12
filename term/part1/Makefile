main:	term.o util.o
	gcc -Wall *.o -o term

term.o:	term.c term.h
	gcc -c term.c

util.o:	util.c term.h
	gcc -c util.c

cleanup:	
	rm *.o
