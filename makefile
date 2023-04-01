asembler.out: asembler.o helpers.o macroDecoder.o binaryMaker.o \
	outputMaker.o FileListFuncs.o MacroListFuncs.o SymbolListFuncs.o
	gcc -Wall -ansi asembler.o helpers.o macroDecoder.o binaryMaker.o \
	outputMaker.o FileListFuncs.o MacroListFuncs.o SymbolListFuncs.o -o asembler.out


SymbolListFuncs.o: SymbolListFuncs.h SymbolListFuncs.c struct.h helpers.o
	gcc -Wall -ansi -c SymbolListFuncs.c -o SymbolListFuncs.o

helpers.o: helpers.h helpers.c struct.h outputMaker.o SymbolListFuncs.o
	gcc -Wall -ansi -c helpers.c -o helpers.o

macroDecoder.o: macroDecoder.h macroDecoder. helpers.o
	gcc -Wall -ansi -c macroDecoder.c -o macroDecoder.o

binaryMaker.o: binaryMaker.h binaryMaker.c helpers.o FileListFuncs.o SymbolListFuncs.o struct.h
	gcc -Wall -ansi -c binaryMaker.c -o binaryMaker.o

outputMaker.o: outputMaker.h outputMaker.c
	gcc -Wall -ansi -c outputMaker.c -o outputMaker.o

FileListFuncs.o: FileListFuncs.h FileListFuncs.c helpers.o
	gcc -Wall -ansi -c FileListFuncs.c -o FileListFuncs.o

MacroListFuncs.o: MacroListFuncs.h MacroListFuncs.c helpers.o FileListFuncs.o
	gcc -Wall -ansi -c MacroListFuncs.c -o MacroListFuncs.o

asembler.o: asembler.c
	gcc -Wall -ansi -c asembler.c -o asembler.o

clean:
	rm -rf *.o