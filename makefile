asembler.out: asembler.o helpers.o macroDecoder.o binaryMaker.o outputMaker.o
	gcc -g -Wall -ansi asembler.o helpers.o macroDecoder.o binaryMaker.o outputMaker.o -o asembler.out

helpers.o:
	gcc -g -Wall -ansi -c helpers.c -o helpers.o

macroDecoder.o:
	gcc -g -Wall -ansi -c macroDecoder.c -o macroDecoder.o

binaryMaker.o:
	gcc -g -Wall -ansi -c binaryMaker.c -o binaryMaker.o

outputMaker.o:
	gcc -g -Wall -ansi -c outputMaker.c -o outputMaker.o
	
asembler.o:
	gcc -g -Wall -ansi -c asembler.c -o asembler.o
