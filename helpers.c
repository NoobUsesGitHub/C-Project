#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "helpers.h"
#include "struct.h"
#include "outputMaker.h"
#include "SymbolListFuncs.h"

/*
    input:nothing
    output: the operators info table(van be seen on page 32)
*/
Operator *createOperatorsTable()
{
    Operator *op_table = (Operator *)malloc(OPERATORS_AMOUNT * sizeof(Operator));
    /* Populate the table: */
    Operator mov =
        {
            .type = MOV,
            .num_of_operands = 2,
            .src_addressing_methods = {0, 1, 2, 3},
            .dst_addressing_methods = {1, 2, 3, -1}};
    memcpy(op_table + MOV, &mov, sizeof(Operator));

    Operator cmp =
        {
            .type = CMP,
            .num_of_operands = 2,
            .src_addressing_methods = {0, 1, 2, 3},
            .dst_addressing_methods = {0, 1, 2, 3}};
    memcpy(op_table + CMP, &cmp, sizeof(Operator));

    Operator add =
        {
            .type = ADD,
            .num_of_operands = 2,
            .src_addressing_methods = {0, 1, 2, 3},
            .dst_addressing_methods = {1, 2, 3, -1}};
    memcpy(op_table + ADD, &add, sizeof(Operator));

    Operator sub =
        {
            .type = SUB,
            .num_of_operands = 2,
            .src_addressing_methods = {0, 1, 2, 3},
            .dst_addressing_methods = {1, 2, 3, -1}};
    memcpy(op_table + SUB, &sub, sizeof(Operator));

    Operator not =
        {
            .type = NOT,
            .num_of_operands = 1,
            .src_addressing_methods = {-1, -1, -1, -1},
            .dst_addressing_methods = {1, 2, 3, -1}};
    memcpy(op_table + NOT, &not, sizeof(Operator));

    Operator clr =
        {
            .type = CLR,
            .num_of_operands = 1,
            .src_addressing_methods = {-1, -1, -1, -1},
            .dst_addressing_methods = {1, 2, 3, -1}};
    memcpy(op_table + CLR, &clr, sizeof(Operator));

    Operator lea =
        {
            .type = LEA,
            .num_of_operands = 2,
            .src_addressing_methods = {1, 2, -1, -1},
            .dst_addressing_methods = {1, 2, 3, -1}};
    memcpy(op_table + LEA, &lea, sizeof(Operator));

    Operator inc =
        {
            .type = INC,
            .num_of_operands = 1,
            .src_addressing_methods = {-1, -1, -1, -1},
            .dst_addressing_methods = {1, 2, 3, -1}};
    memcpy(op_table + INC, &inc, sizeof(Operator));

    Operator dec =
        {
            .type = DEC,
            .num_of_operands = 1,
            .src_addressing_methods = {-1, -1, -1, -1},
            .dst_addressing_methods = {1, 2, 3, -1}};
    memcpy(op_table + DEC, &dec, sizeof(Operator));

    Operator jmp =
        {
            .type = JMP,
            .num_of_operands = 1,
            .src_addressing_methods = {-1, -1, -1, -1},
            .dst_addressing_methods = {1, 2, 3, -1}};
    memcpy(op_table + JMP, &jmp, sizeof(Operator));

    Operator bne =
        {
            .type = BNE,
            .num_of_operands = 1,
            .src_addressing_methods = {-1, -1, -1, -1},
            .dst_addressing_methods = {1, 2, 3, -1}};
    memcpy(op_table + BNE, &bne, sizeof(Operator));

    Operator red =
        {
            .type = RED,
            .num_of_operands = 1,
            .src_addressing_methods = {-1, -1, -1, -1},
            .dst_addressing_methods = {1, 2, 3, -1}};
    memcpy(op_table + RED, &red, sizeof(Operator));

    Operator prn =
        {
            .type = PRN,
            .num_of_operands = 1,
            .src_addressing_methods = {-1, -1, -1, -1},
            .dst_addressing_methods = {0, 1, 2, 3}};
    memcpy(op_table + PRN, &prn, sizeof(Operator));

    Operator jsr =
        {
            .type = JSR,
            .num_of_operands = 1,
            .src_addressing_methods = {-1, -1, -1, -1},
            .dst_addressing_methods = {1, 2, 3, -1}};
    memcpy(op_table + JSR, &jsr, sizeof(Operator));

    Operator rts =
        {
            .type = RTS,
            .num_of_operands = 0,
            .src_addressing_methods = {-1, -1, -1, -1},
            .dst_addressing_methods = {-1, -1, -1, -1}};
    memcpy(op_table + RTS, &rts, sizeof(Operator));

    Operator stop =
        {
            .type = STOP,
            .num_of_operands = 0,
            .src_addressing_methods = {-1, -1, -1, -1},
            .dst_addressing_methods = {-1, -1, -1, -1}};
    memcpy(op_table + STOP, &stop, sizeof(Operator));

    return op_table;
}

/*
    input: the operators info table
    will free the table
*/
void deleteOperatorsTable(Operator *op_table)
{
    free(op_table);
}

/*
input: a string that we want to hash
output: a double that is the encoded string
*/
double hasher(char *str)
{
    double size = strlen(str);
    double hash = 0;
    int i = 0;
    if (str[((int)size) - 1] == '\n')
        size--;
    while (str[i] != '\0')
    {
        if (str[i] != '\n')
            hash += ((int)(str[i])) / (size - i) * 7.0; /*hashing func- takes every letter and its place and calculates a key for it, adding them together*/
        i++;
    }
    return hash;
}

/*
    input: a string pointer
    will fill it with spaces
*/
void clearStr(char *str, int size)
{
    int i;
    for (i = size - 1; i >= 0; i--)
    {
        str[i] = SPACE_CHAR;
    }
}

/*
    input: a pointer to a char
    output: false if it is a space character, otherwise true
*/
bool isLetter(char *bit)
{
    char c = *bit;
    return (*bit != '\n' && isspace(*bit) == 0) ? TRUE : FALSE;
}

/*
    input: a list of strings and their size
    will go through the list and print them
*/
void printList(char **str, int size, FILE *fp)
{

    while (size != 0)
    {
        fprintf(fp, "%s", *str);
        str++;
        size--;
    }
}

/*
    input: a string of .data's input
    output: the number of words it will take
*/
int dataLength(char *str)
{
    int character_count = 0;
    while (*str != '\n' && isLetter(str) == TRUE)
    {
        if (*str == COMMA)
            character_count++;
        str++;
    }
    return character_count + 1;
}

/*
    input: a string
    output: the number of spaces in it
*/
int countSpace(char *str)
{
    int i = 0;
    while (*str != '\n' && *str != '\0')
    {
        if (*str == SPACE_CHAR)
            i++;
        str++;
    }
    return i;
}

/*
    removeRinput: a string
    will remove double spaces
*/
void removeRedundantSpaces(char *str)
{
    int i = 0, j = 0, len = strlen(str);
    char temp[len * 2];
    clearStr(temp, len * 2);
    while (i < len)
    {
        if (isspace(str[i]) != 0)
        { /*is space*/
            if (i == 0)
            {
                i++;
                continue;
            }
            if ((j > 0) && isspace(temp[j - 1]) != 0)
                temp[j - 1] = str[i];
            else
            {
                temp[j] = str[i];
                j++;
            }
        }
        else
        {
            if (str[i] == COMMA && isspace(temp[j - 1]) != 0)
            {
                j--;
            }
            temp[j] = str[i];
            j++;
            if (str[i] == COMMA)
            {
                temp[j] = SPACE_CHAR;
                j++;
            }
        }
        i++;
    }
    if (temp[j - 1] == SPACE_CHAR || str[j - 1] == '\t')
        j--;
    temp[j] = '\0';
    strcpy(str, temp);
}

/*
    input: a string that should represent a operator
    output: the operator type of it, if it doesnt exist, ERROR_NA=-1
*/
OperatorType stringToOperatorType(char *operator_name)
{
    int i = strlen(operator_name);
    char str[strlen(operator_name)];
    strcpy(str, operator_name);
    for (; i >= 0; i--)
    {
        str[i] = tolower(str[i]);
    }
    if (operator_name[strlen(operator_name) - 1] == '\n')
    {
        operator_name[strlen(operator_name) - 1] = '\0';
        str[strlen(operator_name) - 1] = '\0';
    }
    if (strcmp(operator_name, "mov") == 0 || strcmp(str, "MOV") == 0)
    {
        return MOV;
    }
    else if (strcmp(operator_name, "cmp") == 0 || strcmp(str, "CMP") == 0)
    {
        return CMP;
    }
    else if (strcmp(operator_name, "add") == 0 || strcmp(str, "ADD") == 0)
    {
        return ADD;
    }
    else if (strcmp(operator_name, "sub") == 0 || strcmp(str, "SUB") == 0)
    {
        return SUB;
    }
    else if (strcmp(operator_name, "not") == 0 || strcmp(str, "NOT") == 0)
    {
        return NOT;
    }
    else if (strcmp(operator_name, "clr") == 0 || strcmp(str, "CLR") == 0)
    {
        return CLR;
    }
    else if (strcmp(operator_name, "lea") == 0 || strcmp(str, "LEA") == 0)
    {
        return LEA;
    }
    else if (strcmp(operator_name, "inc") == 0 || strcmp(str, "INC") == 0)
    {
        return INC;
    }
    else if (strcmp(operator_name, "dec") == 0 || strcmp(str, "DEC") == 0)
    {
        return DEC;
    }
    else if (strcmp(operator_name, "jmp") == 0 || strcmp(str, "JMP") == 0)
    {
        return JMP;
    }
    else if (strcmp(operator_name, "bne") == 0 || strcmp(str, "BNE") == 0)
    {
        return BNE;
    }
    else if (strcmp(operator_name, "red") == 0 || strcmp(str, "RED") == 0)
    {
        return RED;
    }
    else if (strcmp(operator_name, "prn") == 0 || strcmp(str, "PRN") == 0)
    {
        return PRN;
    }
    else if (strcmp(operator_name, "jsr") == 0 || strcmp(str, "JSR") == 0)
    {
        return JSR;
    }
    else if (strcmp(operator_name, "rts") == 0 || strcmp(str, "RTS") == 0)
    {
        return RTS;
    }
    else if (strcmp(operator_name, "stop") == 0 || strcmp(str, "STOP") == 0)
    {
        return STOP;
    }
    return ERROR_NA;
}

/*
    input: the Symbol table, the final number of lines
    will add IC to all data lines (step 17)
*/
void addToData(Symbol *dataHeader, int IC)
{
    while (dataHeader != NULL)
    {
        if (dataHeader->type == DATA || dataHeader->type == STRING)
            dataHeader->line = dataHeader->line + IC;
        dataHeader = dataHeader->next;
    }
}

/*
    input: opcode and the hashtable of opcodes
    output: the number of operators for that opcode
*/
int getNumOfOperands(OperatorType type, Operator *op_table)
{
    if (type == ERROR_NA)
        return -1;
    return op_table[type].num_of_operands;
}

/*
    input: a string and the Data counter
    will print the individual numbers as binary and increase the DC
*/
void dumpDataOpers(char *str, int *cnt, int mode, FILE *fp)
{
    int size = strlen(str);
    char temp[size];
    char binaryChar[BINARY_LINE_SIZE];
    strcpy(binaryChar, "00000000000000");
    int value, i = 0, j = 0;
    while (*str != '\n' && *str != '\0' && str != NULL && massIsSpace(str) != 1)
    {
        /*will run on the string until i finish the number or meet "," */
        if (*str == COMMA)
        {
            strcpy(binaryChar, "00000000000000");
            value = atoi(temp);
            intToBinary(binaryChar, value);
            if (mode != SIMULATION)
            {
                fprintf(fp, "%d\t%s\n", *cnt, binaryChar);
                *cnt = *cnt + 1;
            }
            clearStr(temp, size);
            str++;
        }
        else
        {
            temp[i] = *str;
            str++;
            i++;
        }
    }
    if (temp != NULL && massIsSpace(temp) != 1)
    {
        strcpy(binaryChar, "00000000000000");
        value = atoi(temp);
        intToBinary(binaryChar, value);
        if (mode != SIMULATION)
        {
            fprintf(fp, "%d\t%s\n", *cnt, binaryChar);
            *cnt = *cnt + 1;
        }
        clearStr(temp, size);
    }
}

/*
    input: a string and the Data counter
    will print the individual letters as binary and increase the DC
*/
void dumpStr(char *oper, int *cnt, int mode, FILE *fp)
{
    int size = strlen(oper);
    char binaryChar[BINARY_LINE_SIZE];
    int value;
    while (*oper != '\0')
    {
        value = (int)(*oper);
        strcpy(binaryChar, "00000000000000");
        intToBinary(binaryChar, value);
        if (mode != SIMULATION)
        {
            fprintf(fp, "%d\t%s\n", *cnt, binaryChar);
            *cnt = *cnt + 1;
        }
        oper++;
    }
}

/*
    input: a placeholder string and a number to change to binary
    will leave the number in binary (in 12 bits) in the placeholder str
*/
void intToBinary(char *placeHolderString, int value)
{
    int i = 0, size = strlen(placeHolderString);
    for (i = 0; i < size; i++)
        if (value & (1 << (size - 1 - i)))
        {
            placeHolderString[i] = '1';
        }
        else
        {
            placeHolderString[i] = '0';
        }
    placeHolderString[size] = '\0';
}
/*
    input: a string
    output: the number of register it is if it exists, if not, -1
*/
int realRegister(char *str)
{
    char reg[3];
    int i = 0;

    for (; i < 8; i++)
    {
        sprintf(reg, "r%d", i);
        if (strcmp(str, reg) == 0)
            return i;
    }
    return -1;
}

/*
    input: An operator, the two operands adresstypes and the Operator info table
    output: true if the operands accsespts these operands, else false

*/
bool isAddTypeCorrect(OperatorType op_type, int adTypeOper1, int adTypeOper2, Operator *op_table, int opersCnt)
{
    switch (opersCnt)
    {
    case 0:

        if (adTypeOper1 == -1 && adTypeOper2 == -1)
            return TRUE;
        break;

    case 1:
        if (adTypeOper1 == -1)
            adTypeOper1 = adTypeOper2;
        if (existInAddressType(adTypeOper1, op_table[op_type].src_addressing_methods) || existInAddressType(adTypeOper1, op_table[op_type].dst_addressing_methods))
        {
            return TRUE;
        }
        break;
    case 2:
        if (adTypeOper1 == -1 || adTypeOper2 == -1)
            return FALSE;
        if (op_type == ERROR_NA)
            return FALSE;

        if (op_type == JMP || op_type == JSR || op_type == BNE)
            return TRUE;

        if (existInAddressType(adTypeOper1, op_table[op_type].src_addressing_methods) && existInAddressType(adTypeOper2, op_table[op_type].dst_addressing_methods))
        {
            return TRUE;
        }
        break;
    }
    return FALSE;
}

/*
    input: an addressing type and an array of addressing types
    output: true if this address type exists, else false
    will run until end of array or it meets a -1 (which means end of array instead of a certain address type)
*/
bool existInAddressType(int ad_type, int addressing_methods[])
{
    int i = 0;
    while (i < 4 && addressing_methods[i] != -1)
    {
        if (ad_type == addressing_methods[i])
            return TRUE;
        else
            i++;
    }
    return FALSE;
}

/*
  input: two strs, from and two, and how many chars to copy
  will copy the chars from the from to to
*/
void strcpyBySteps(char *to, char *from, int steps)
{
    while (steps > 0)
    {
        *to = *from;
        to++;
        from++;

        steps--;
    }
}

void dumpFullInstruction(char *label, char *opcode, char *oper1, char *oper2, int opersCnt, int *IC, int mode, Operator *op_table, Symbol *sym_list, FILE *fp)
{
    int adTypeOper1 = 0, adTypeOper2 = 0;
    OperatorType op_type = stringToOperatorType(opcode);
    if (opersCnt != getNumOfOperands(op_type, op_table) && (op_type != JMP && op_type != BNE && op_type != JSR)) /*do we have more than required operators*/
        fprintf(stdout, "opcode %s has more operators than expected\n", opcode);

    /*take the types of two opers*/

    adTypeOper1 = checkAddressType(oper1, op_type, mode, sym_list);
    adTypeOper2 = checkAddressType(oper2, op_type, mode, sym_list);
    if (!isAddTypeCorrect(op_type, adTypeOper1, adTypeOper2, op_table, opersCnt))
    {
        fprintf(stdout, "incorrect address type for one of the operators for %s in line %d\n", opcode, *IC);
        adTypeOper1 = 0;
        adTypeOper2 = 0; /*adding dummy info*/
    }

    /*print the opcode binary*/
    calculateOpcodeBinaryAndPrint(op_type, adTypeOper1, adTypeOper2, mode, IC, sym_list, label, fp);
    /*print the opers binary*/
    calculateOperatorsBinaryAndPrint(oper1, oper2, adTypeOper1, adTypeOper2, mode, IC, sym_list, fp);
}

void calculateOperatorsBinaryAndPrint(char *oper1, char *oper2, int adTypeOper1, int adTypeOper2, int mode, int *IC, Symbol *sym_list, FILE *fp)
{
    char binary[BINARY_LINE_SIZE], temp[7];
    strcpy(binary, "00000000000000");
    strcpy(temp, "000000");

    if (adTypeOper1 == adTypeOper2 && adTypeOper2 == 3)
    {
        /*if both registers, we set them as one
        reg1+reg2+A(00)
        */
        intToBinary(binary, realRegister(oper1));
        shiftLeftChar(binary, 6);

        intToBinary(temp, realRegister(oper2));
        strcpyBySteps(binary + 8, temp, 6);
        shiftLeftChar(binary, 2);
        if (mode != SIMULATION)
            fprintf(fp, "%d\t%s\n", *IC, binary);
        *IC = *IC + 1;
    }
    else
    {
        /*besides the above, we have them working apart*/

        switch (adTypeOper1)
        {
        case -1:
            break;

        case 0: /*number*/
            /*oper1 +A(00)*/
            intToBinary(binary, atoi(oper1 + 1));
            shiftLeftChar(binary, 2);
            strcpyBySteps(binary + BINARY_LINE_SIZE - 3, temp + 2, 2);
            if (mode != SIMULATION)
                fprintf(fp, "%d\t%s\n", *IC, binary);
            *IC = *IC + 1;
            break;

        case 1: /*label*/
            if (mode == EXECUTION)
                checkIfExternal(oper1, *IC + 1, sym_list);
            if (existInSymbolTable(oper1, sym_list, SIMULATION) != -1 && symbolTypeFromTable(oper1, sym_list) == EXTERN)
            {
                /*oper1+E(01)*/
                intToBinary(binary, existInSymbolTable(oper1, sym_list, EXECUTION));
                shiftLeftChar(binary, 2);
                temp[3] = '1';
                temp[2] = '0';
                strcpyBySteps(binary + BINARY_LINE_SIZE - 3, temp + 2, 2);
                if (mode != SIMULATION)
                    fprintf(fp, "%d\t%s\n", *IC, binary);
                *IC = *IC + 1;
            }
            else
            {
                /*oper1+R(10)*/

                intToBinary(binary, existInSymbolTable(oper1, sym_list, EXECUTION));
                shiftLeftChar(binary, 2);
                temp[3] = '0';
                temp[2] = '1';
                strcpyBySteps(binary + BINARY_LINE_SIZE - 3, temp + 2, 2);
                if (mode != SIMULATION)
                    fprintf(fp, "%d\t%s\n", *IC, binary);
                *IC = *IC + 1;
            }
            break;
        case 3: /*register*/
            /*regCode(oper1)+A(00) */
            intToBinary(binary, realRegister(oper1));
            shiftLeftChar(binary, 7);
            if (mode != SIMULATION)
                fprintf(fp, "%d\t%s\n", *IC, binary);
            *IC = *IC + 1;
            break;
        }

        strcpy(binary, "00000000000000");
        strcpy(temp, "0000");
        switch (adTypeOper2)
        {
        case -1:
            break;

        case 0: /*number*/
            /*oper2 +A(00)*/
            intToBinary(binary, atoi(oper2 + 1));
            shiftLeftChar(binary, 2);
            strcpyBySteps(binary, temp + 2, 2);
            if (mode != SIMULATION)
                fprintf(fp, "%d\t%s\n", *IC, binary);
            *IC = *IC + 1;
            break;

        case 1: /*label*/
            if (mode == EXECUTION)
                checkIfExternal(oper2, *IC + 1, sym_list);
            if (existInSymbolTable(oper2, sym_list, SIMULATION) != -1 && symbolTypeFromTable(oper2, sym_list) == EXTERN)
            {
                /*oper2+E(01)*/
                intToBinary(binary, existInSymbolTable(oper2, sym_list, EXECUTION));
                shiftLeftChar(binary, 2);
                temp[3] = '1';
                temp[2] = '0';
                strcpyBySteps(binary + BINARY_LINE_SIZE - 3, temp + 2, 2);
                if (mode != SIMULATION)
                    fprintf(fp, "%d\t%s\n", *IC, binary);
                *IC = *IC + 1;
            }
            else
            {
                /*oper2+R(10)*/
                intToBinary(binary, existInSymbolTable(oper2, sym_list, EXECUTION));
                shiftLeftChar(binary, 2);
                temp[3] = '0';
                temp[2] = '1';
                strcpyBySteps(binary + BINARY_LINE_SIZE - 3, temp + 2, 2);
                if (mode != SIMULATION)
                    fprintf(fp, "%d\t%s\n", *IC, binary);
                *IC = *IC + 1;
            }
            break;
        case 3: /*register*/
            /*regCode(oper2)+A(00) */
            intToBinary(binary, realRegister(oper2));
            shiftLeftChar(binary, 2);
            strcpyBySteps(binary + BINARY_LINE_SIZE - 3, temp + 2, 2);
            if (mode != SIMULATION)
                fprintf(fp, "%d\t%s\n", *IC, binary);
            *IC = *IC + 1;
            break;
        }
    }
}

/*
    input: the type of the operator, the address types of the operands, the mode, the instruction counter, the symbol info table and the label
    will turn the opcode to binary, if there is a label(aka we are jumping, will print that too)
*/
void calculateOpcodeBinaryAndPrint(OperatorType op_type, int adTypeOper1, int adTypeOper2, int mode, int *IC, Symbol *sym_list, char *label, FILE *fp)
{
    bool needToPrintLabel = FALSE;
    char binary[BINARY_LINE_SIZE], temp[5];
    strcpy(binary, "00000000000000");
    strcpy(temp, "0000");

    /*first, the opcode 8-10*/
    intToBinary(temp, (int)op_type);
    strcpyBySteps(binary + 4, temp, 4);
    strcpy(temp, "0000");

    /*2-3 dst operand*/
    if (adTypeOper2 != -1)
    {
        intToBinary(temp, adTypeOper2);
        strcpyBySteps(binary + 10, temp + 2, 2);
        strcpy(temp, "0000");
    }
    /*4-5 src operand*/
    if (adTypeOper1 != -1)
    {
        intToBinary(temp, adTypeOper1);
        strcpyBySteps(binary + 8, temp + 2, 2);
        strcpy(temp, "0000");
    }
    /*10-13 is for only address type 2 JMPS*/
    if (op_type == JMP || op_type == JSR || op_type == BNE)
    {
        /*first 12-13*/
        if (adTypeOper1 == 2)
        {
            temp[3] = '1';
            temp[2] = '0';
            strcpyBySteps(binary, temp + 2, 2);
        }
        else if (adTypeOper1 == 3)
        {
            temp[3] = '1';
            temp[2] = '1';
            strcpyBySteps(binary, temp + 2, 2);
        }
        /*second 10-11*/
        if (adTypeOper2 == 2)
        {
            temp[3] = '1';
            temp[2] = '0';
            strcpyBySteps(binary + 2, temp + 2, 2);
        }
        else if (adTypeOper2 == 3)
        {
            temp[3] = '1';
            temp[2] = '1';
            strcpyBySteps(binary + 2, temp + 2, 2);
        }
        needToPrintLabel = TRUE;
    }
    if (mode != SIMULATION)
        fprintf(fp, "%d\t%s\n", *IC, binary);
    *IC = *IC + 1;
    strcpy(binary, "00000000000000");
    if (needToPrintLabel)
    {
        if (mode == EXECUTION)
            checkIfExternal(label, *IC, sym_list);
        intToBinary(binary, existInSymbolTable(label, sym_list, EXECUTION));
        shiftLeftChar(binary, 2);
        strcpy(binary + 12, "10");
        if (mode != SIMULATION)
            fprintf(fp, "%d\t%s\n", *IC, binary);
        *IC = *IC + 1;
    }
}

/*
    input: a string and the number of chars to take back a step
    will push the chars X steps to the left
*/
void shiftLeftChar(char *binary, int steps)
{
    int size = strlen(binary);
    char temp[size + 1];
    memset(temp, '0', size);
    int i = steps, j = 0;
    while (i < size)
    {
        temp[j] = binary[i];
        i++;
        j++;
    }
    memcpy(binary, temp, (size + 1) * sizeof(char));
    binary[size] = '\0';
}
/*
    input: the string of the operand, the type of the operator, the mode and the symbol table
    output: the address type, per page 19
*/
int checkAddressType(char *oper, OperatorType opcode, int mode, Symbol *sym_list)
{
    char *bit = oper;
    if (*bit == '#')
        return 0;

    if (realRegister(oper) != -1)
        return 3;

    if (oper != NULL && massIsSpace(oper) == 1)
        return -1;

    if (opcode == JMP || opcode == BNE || opcode == JSR)
        return 2;

    if (mode == SIMULATION || (mode != SIMULATION && existInSymbolTable(oper, sym_list, SIMULATION) != -1))
        return 1;
    return -1;
}

/*
    input: the string for the operator that we recieved and a placeholder for the next and the label
    output: the number of operands we have if we need to split the operands and label
*/
int breakDownJumps(char *oper1, char *oper2, char *label)
{
    /*if this a normal jump, will be not split because it has a label, else split to two operands */
    bool skip = FALSE;
    char *bit = oper1;
    char *label_pointer = label;
    memset(label, '\0', MAX_LABEL_SIZE * sizeof(char));
    /*collecting a label, we have one for sure*/
    while (*bit != '(' && *bit != '\n' && *bit != '\0' && isspace(*bit) == 0)
    {
        *label_pointer = *bit;
        bit++;
        label_pointer++;
    }

    /*skipping forward if we need to*/
    while (isspace(*bit) != 0)
        bit++;
    /*checking if we have operands*/
    if (*bit == '(')
        bit++;
    else
        return 1;

    int i = 0, j = 0;
    while (*bit != '\n' && *bit != '\0')
    {
        oper1[i] = *bit;
        i++;
        bit++;
    }
    oper1[i] = '\0';
    bit = oper2;
    while (*bit != '\n' && *bit != '\0' && !skip)
    {
        if (*bit == ')')
        {
            skip = TRUE;
        }
        oper2[j] = *bit;
        j++;
        bit++;
    }

    if (j > 0)
    {
        if (oper2[j - 1] == ')')
            j--;
        oper2[j] = '\0';
    }

    return strlen(oper2) > 0 ? 2 : 1;
}

/*
    input: a header of the symbols table, the file name, a data symbol type, and the extention
    will push all the data symbols of that type to a file
*/
void dumpSymbols(Symbol *header, char *fileName, Stype stype, char *extention)
{
    int size = strlen(fileName) + 1;
    char newName[size];
    char binary[BINARY_LINE_SIZE];
    bool found_any = FALSE;
    char *bit = NULL;
    strcpy(binary, "00000000000000");
    strcpy(newName, fileName);
    strcpyBySteps(newName + strlen(newName) + 1 - strlen(extention), extention, 4);
    newName[size] = 0;
    FILE *fp = fopen(newName, "w");
    if (fp == NULL)
        fprintf(stdout, "we had trouble opening a %s file", extention);
    while (header != NULL)
    {
        if (stype != EXTERN)
        {
            if (header->type == stype || (header->externalType == stype && header->externalType == CODE) || (stype == DATA && header->type == STRING))
            {
                found_any = TRUE;
                intToBinary(binary, header->line);
                bit = binary;
                while (*bit != '\0')
                {
                    *bit = binaryTranslate(*bit);
                    bit++;
                }
                fprintf(fp, "%s\t%s\n", header->name, binary);
                strcpy(binary, "00000000000000");
            }
            else
            {
                if (header->type != stype && header->externalType == stype)
                {
                    found_any = TRUE;
                    intToBinary(binary, header->line);
                    bit = binary;
                    while (*bit != '\0')
                    {
                        *bit = binaryTranslate(*bit);
                        bit++;
                    }
                    fprintf(fp, "%s\t%s\n", header->name, binary);
                    strcpy(binary, "00000000000000");
                }
            }
        }
        else
        {
            if (header->type == CODE && header->externalType == EXTERN)
            {
                found_any = TRUE;
                intToBinary(binary, header->line);
                bit = binary;
                while (*bit != '\0')
                {
                    *bit = binaryTranslate(*bit);
                    bit++;
                }
                fprintf(fp, "%s\t%s\n", header->name, binary);
                strcpy(binary, "00000000000000");
            }
        }
        header = header->next;
    }
    fclose(fp);
    if (!found_any)
        remove(newName);
}

/*
input: the header of the list of symbols, the Instruction counter and file to print to
will create an array and print the symbols ordered by line
*/
void dumpSymbolsToMainFile(Symbol *header, int *IC, FILE *fp, int mode)
{
    int numOfSymbols = countSymbols(header);
    Symbol *arr[numOfSymbols];
    fillSymArr(arr, numOfSymbols, header);
    qsort(arr, numOfSymbols, sizeof(Symbol *), SymbolCompare);

    int i = 0;
    numOfSymbols = countSymbols(header);
    for (; i < numOfSymbols; i++)
    {
        switch (arr[i]->type)
        {
        case STRING:
            dumpStr(arr[i]->input, IC, mode, fp);
            break;

        case DATA:
            dumpDataOpers(arr[i]->input, IC, mode, fp);
            break;
        }
    }
}

/*
    input: a string(possibly a label) a line number and the symbol list
    if the label represents an external symbol we will add it to the symbol table to add to the .ext file
*/
void checkIfExternal(char *oper, int line, Symbol *sym_list)
{
    if (existInSymbolTable(oper, sym_list, SIMULATION) != -1 && symbolTypeFromTable(oper, sym_list) == EXTERN)
        addSymbolToList(sym_list, oper, CODE, line, NULL, EXTERN);
}

/*
    input: a string
    output: 1- if the whole string is a space character,else 0
*/
int massIsSpace(char *pch)
{
    int space = isspace(*pch);
    while (*pch != '\0' && *pch != '\n')
    {
        space = space && isspace(*pch);
        pch++;
    }
    return space;
}