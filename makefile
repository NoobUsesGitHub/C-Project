asembler.out: asembler.o helpers.o macroDecoder.o binaryMaker.o outputMaker.o FileListFuncs.o MacroListFuncs.o
	gcc -Wall -ansi asembler.o helpers.o macroDecoder.o binaryMaker.o outputMaker.o  FileListFuncs.o MacroListFuncs.o -o asembler.out

helpers.o:
	gcc -Wall -ansi -c helpers.c -o helpers.o

macroDecoder.o:
	gcc -Wall -ansi -c macroDecoder.c -o macroDecoder.o

binaryMaker.o:
	gcc -Wall -ansi -c binaryMaker.c -o binaryMaker.o

outputMaker.o:
	gcc -Wall -ansi -c outputMaker.c -o outputMaker.o

FileListFuncs.o:
	gcc -Wall -ansi -c FileListFuncs.c -o FileListFuncs.o


MacroListFuncs.o:
	gcc -Wall -ansi -c MacroListFuncs.c -o MacroListFuncs.o

asembler.o:
	gcc -Wall -ansi -c asembler.c -o asembler.o
