asembler.out: asembler.o helpers.o macroDecoder.o binaryMaker.o \
	outputMaker.o FileListFuncs.o MacroListFuncs.o SymbolListFuncs.o
	gcc -Wall -ansi asembler.o helpers.o macroDecoder.o binaryMaker.o \
	outputMaker.o FileListFuncs.o MacroListFuncs.o SymbolListFuncs.o -o asembler.out


SymbolListFuncs.o: SymbolListFuncs.c
	gcc -Wall -ansi -c SymbolListFuncs.c -o SymbolListFuncs.o

helpers.o: SymbolListFuncs.o helpers.c
	gcc -Wall -ansi -c helpers.c SymbolListFuncs.o -o helpers.o

macroDecoder.o: MacroListFuncs.o macroDecoder.c
	gcc -Wall -ansi -c macroDecoder.c MacroListFuncs.o -o macroDecoder.o

binaryMaker.o: FileListFuncs.o SymbolListFuncs.o binaryMaker.c
	gcc -Wall -ansi -c binaryMaker.c FileListFuncs.o SymbolListFuncs.o -o binaryMaker.o

outputMaker.o: outputMaker.c
	gcc -Wall -ansi -c outputMaker.c -o outputMaker.o

FileListFuncs.o: FileListFuncs.c
	gcc -Wall -ansi -c FileListFuncs.c -o FileListFuncs.o

MacroListFuncs.o: MacroListFuncs.c
	gcc -Wall -ansi -c MacroListFuncs.c -o MacroListFuncs.o

asembler.o: asembler.c
	gcc -Wall -ansi -c asembler.c -o asembler.o

clean:
	rm -rf *.o