asembler.out: helper.o macroDecoder.o 
	gcc -g -Wall -ansi asembler.o helper.o macroDecoder.o -o asembler.out

helper.o:
	gcc -g -Wall -ansi helper.c -o helper.o


macroDecoder.o:
	gcc -g -Wall -ansi macroDecoder.c -o macroDecoder.o

asembler.o:
	gcc -g -Wall -ansi asembler.c -o asembler.o
