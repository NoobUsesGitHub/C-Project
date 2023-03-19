asembler.out: helpers.o macroDecoder.o 
	gcc -g -Wall -ansi asembler.o helpers.o macroDecoder.o -o asembler.out

helpers.o:
	gcc -g -Wall -ansi helpers.c -o helpers.o


macroDecoder.o:
	gcc -g -Wall -ansi macroDecoder.c -o macroDecoder.o

asembler.o:
	gcc -g -Wall -ansi asembler.c -o asembler.o
