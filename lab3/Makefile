main:	parser.o util.o
	gcc -Wall *.o -o parser

parser.o:	parser.c parser.h
	gcc -c parser.c

util.o:	util.c parser.h
	gcc -c util.c

cleanup:	
	rm *.o
