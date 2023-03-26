#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"

void calculateOpcodeBinaryAndPrint(OperatorType op_type, int adTypeOper1, int adTypeOper2, int mode, int *IC, Symbol *sy_table, char *label)
{
  bool needToPrintLabel = FALSE;
  char binary[15];
  strcpy(binary, "00000000000000\0");
  char temp[5];
  strcpy(temp, "0000\0");
  /*first, the opcode 8-10*/
  intToBinary(temp, (int)op_type);
  strcpyBySteps(binary + 4, temp, 4);
  strcpy(temp, "0000\0");

  /*2-3 dst operand*/
  intToBinary(temp, adTypeOper2);
  strcpyBySteps(binary + 10, temp + 2, 2);
  strcpy(temp, "0000\0");
  /*4-5 src operand*/
  intToBinary(temp, adTypeOper1);
  strcpyBySteps(binary + 8, temp + 2, 2);
  strcpy(temp, "0000\0");
  /*10-13 is for only address type 2 JMPS*/
  if (op_type == JMP || op_type == JSR || op_type == BNE)
  {
    /*first 12-13*/
    if (adTypeOper1 == 2)
    {
      temp[3]='1';
      temp[2]='0';
      strcpyBySteps(binary, temp, 2);
    }
    else if (adTypeOper1 == 3)
    {
      temp[3]='1';
      temp[2]='0';
      strcpyBySteps(binary, temp, 2);
    }
    /*second 10-11*/
    if (adTypeOper2 == 2)
    {
      temp[3]='1';
      temp[2]='0';
      strcpyBySteps(binary+2, temp, 2);
    }
    else if (adTypeOper2 == 3)
    {
      temp[3]='1';
      temp[2]='0';
      strcpyBySteps(binary+2, temp, 2);
    }
    needToPrintLabel = TRUE;
  } /*to do-ARE for operands*/

  printf("%d  %s\n", *IC, binary);
  *IC++;
  strcpy(binary, "00000000000000\0");
  if (needToPrintLabel)
  {
    intToBinary(binary, existInSymbolTable(label, sy_table));
    rollBack(binary, 2);
    strcpy(binary + 12, "10");

    printf("%d  %s", *IC, binary);
    *IC++;
  }
}

int main()
{
  char binary[15];
  Symbol *sy_table;
  constSymbol(&sy_table);
  addSymbolToList(sy_table, "AAA", CODE, 11);
  strcpy(binary, "00000000000100\0");
  int IC = 11;
  calculateOpcodeBinaryAndPrint(BNE, 0, 3, SIMULATION, &IC, sy_table, "AAA");
  rollBack(binary, 2);
  return 0;
}