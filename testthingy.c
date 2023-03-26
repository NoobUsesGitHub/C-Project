#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"

int main()
{
  char binary[15];
  Symbol *sy_table;
  constSymbol(&sy_table);
  addSymbolToList(sy_table, "AAA", CODE, 11);
  strcpy(binary, "00000000000100\0");
  int IC = 11;
  calculateOpcodeBinaryAndPrint(BNE, 0, 0, SIMULATION, &IC, sy_table, "AAA");
  shiftLeftChar(binary, 2);
  return 0;
}