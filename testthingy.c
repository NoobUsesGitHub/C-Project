#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"


void calculateOpcodeBinaryAndPrint(OperatorType op_type, int adTypeOper1, int adTypeOper2, int mode, int *IC, Symbol *sy_table,char *label)
{
    bool needToPrintLabel = ;
    char binary[15];
    strcpy(binary, "00000000000000\0");
    char temp[5];
    strcpy(temp, "0000\0");
    /*first, the opcode 8-10*/
    intToBinary(temp, (int)op_type);
    strcpy(binary + 4, temp);
    strcpy(temp, "0000\0");

    /*2-3 dst operand*/
    intToBinary(temp, adTypeOper2);
    strcpy(binary + 9, temp + 2);
    strcpy(temp, "0000\0");
    /*4-5 dst operand*/
    intToBinary(temp, adTypeOper1);
    strcpy(binary + 7, temp + 2);
    strcpy(temp, "0000\0");
    /*10-13 is for only address type 2 JMPS*/
    if (op_type == JMP || op_type == JSR || op_type == BNE)
    {
        /*first 12-13*/
        if (adTypeOper1 == 2)
            strcpy(binary, "11");
        else if (adTypeOper1 == 3)
            strcpy(binary, "01");
        /*first 10-11*/
        if (adTypeOper1 == 2)
            strcpy(binary + 2, "11");
        else if (adTypeOper1 == 3)
            strcpy(binary + 2, "01");
        needToPrintLabel = TRUE;
    } /*to do-ARE for operands*/

    printf("%d  %s", *IC, binary);
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
  strcpy(binary,"00000000000100\0";
  rollBack(binary, 2);
  return 0;
}
