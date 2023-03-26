#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "helpers.h"
#include "struct.h"
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
    /*maybe change to while*/
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
    while (*str != '\n' && isLetter(str) == TRUE)
    {
        if (*str == SPACE_CHAR)
            i++;
        str++;
    }
    return i + 1;
}

void removeRedundantSpaces(char *str)
{
    int i, j, len;
    len = strlen(str); /*to change*/
    j = 0;
    for (i = 0; i < len; i++)
    {
        if (isspace(str[i]) == 0)
        {
            if (i > 0 && str[i] == COMMA && isspace(str[j - 1]))
            {
                str[j - 1] = str[i];
                continue;
            }
            str[j] = str[i];
            j++;
        }
        else if (i > 0 && isspace(str[i - 1]) == 0)
        {
            str[j] = SPACE_CHAR;
            j++;
        }
    }
    if (str[j - 1] == SPACE_CHAR || str[j - 1] == '\t')
        j--;
    str[j] = '\0';
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

    if (strcmp(operator_name, "mov") || strcmp(str, "mov"))
    {
        return MOV;
    }
    else if (strcmp(operator_name, "cmp") || strcmp(str, "cmp"))
    {
        return CMP;
    }
    else if (strcmp(operator_name, "add") || strcmp(str, "add"))
    {
        return ADD;
    }
    else if (strcmp(operator_name, "sub") || strcmp(str, "sub"))
    {
        return SUB;
    }
    else if (strcmp(operator_name, "not") || strcmp(str, "not"))
    {
        return NOT;
    }
    else if (strcmp(operator_name, "clr") || strcmp(str, "clr"))
    {
        return CLR;
    }
    else if (strcmp(operator_name, "lea") || strcmp(str, "lea"))
    {
        return LEA;
    }
    else if (strcmp(operator_name, "inc") || strcmp(str, "inc"))
    {
        return INC;
    }
    else if (strcmp(operator_name, "dec") || strcmp(str, "dec"))
    {
        return DEC;
    }
    else if (strcmp(operator_name, "jmp") || strcmp(str, "jmp"))
    {
        return JMP;
    }
    else if (strcmp(operator_name, "bne") || strcmp(str, "bne"))
    {
        return BNE;
    }
    else if (strcmp(operator_name, "red") || strcmp(str, "red"))
    {
        return RED;
    }
    else if (strcmp(operator_name, "prn") || strcmp(str, "prn"))
    {
        return PRN;
    }
    else if (strcmp(operator_name, "jsr") || strcmp(str, "jsr"))
    {
        return JSR;
    }
    else if (strcmp(operator_name, "rts") || strcmp(str, "rts"))
    {
        return RTS;
    }
    else if (strcmp(operator_name, "stop") || strcmp(str, "stop"))
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
    while (dataHeader->next != NULL)
    {
        if (dataHeader->type == DATA)
            dataHeader->line = dataHeader->line + IC;
        dataHeader++;
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
void dumpDataOpers(char *str, int *DC, int mode)
{

    int size = strlen(str);
    char temp[size];
    char binaryChar[14];
    int value, i = 0;
    while (*str != '\n')
    {
        /*will run on the string until i finish the number or meet "," */
        if (*str == COMMA)
        {
            value = atoi(temp);
            intToBinary(binaryChar, value);
            if (mode != SIMULATION)
                printf("%d  %s", *DC, binaryChar);
            *DC++;
            clearStr(temp, size);
        }
        else
        {
            temp[i] = *str;
            str++;
            i++;
        }
    }
    if (*temp != SPACE_CHAR)
    {

        value = atoi(temp);
        intToBinary(binaryChar, value);
        if (mode != SIMULATION)
            printf("%d  %s", *DC, binaryChar);
        *DC++;
        clearStr(temp, size);
        *DC++;
    }
}

/*
    input: a string and the Data counter
    will print the individual letters as binary and increase the DC
*/
void dumpStr(char *oper, int *DC, int mode)
{
    int size = strlen(oper);
    char binaryChar[14];
    int value;
    while (*oper != '\0' && *oper != '\n')
    {
        value = (int)(*oper);
        intToBinary(binaryChar, value);
        if (mode != SIMULATION)
            printf("%d  %s", *DC, binaryChar);
        *DC++;
        oper++;
    }
    printf("%d  %s", *DC, binaryChar);
    *DC++;
}

/*
    input: a placeholder string and a number to change to binary
    will leave the number in binary (in 12 bits) in the placeholder str
*/
void intToBinary(char *binaryChar, int value)
{
    int bufferSize=strlen(binaryChar);
int i =0;
    for (i = bufferSize - 1; i >= 0; i--) {
        if ((value >> i) & 1) {
            binaryChar[i]='1';
        } else {
            binaryChar[i]='0';
        }
    }
}


    /*binaryChar[size+1] = '\0';*/
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
bool isAddTypeCorrect(OperatorType op_type, int adTypeOper1, int adTypeOper2, Operator *op_table)
{
    if (adTypeOper1 == -1 || adTypeOper2 == -1)
        return FALSE;
    if (op_type == ERROR_NA)
        return FALSE;
    if (existInAddressType(adTypeOper1, op_table[op_type].src_addressing_methods) && existInAddressType(adTypeOper2, op_table[op_type].dst_addressing_methods))
    {
        return TRUE;
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
    not done yet
    general Idea- will recieve label, opcode,operator1 operator2 and then code them up to binary



void dumpFullInstruction(char *label, char *opcode, char *oper1, char *oper2, int opersCnt, int *IC, int mode, Operator *op_table, Symbol *sym_table)
{
    int adTypeOper1 = 0, adTypeOper2 = 0;
    OperatorType op_type = stringToOperatorType(opcode);
    if (opersCnt != getNumOfOperands(op_type, op_table)) /*do we have more than required operators
        printf("nope, not right");

    /*take the types of two opers

    adTypeOper1 = checkAddressType(oper1, op_type, mode, sym_table);
    adTypeOper2 = checkAddressType(oper2, op_type, mode, sym_table);
    if (!isAddTypeCorrect(op_type, adTypeOper1, adTypeOper2, op_table))
    {
        printf("incorrect address type for one of the operators for %s in %d", opcode, *IC);
        adTypeOper1 = 0;
        adTypeOper2 = 0; /*adding dummy info
    }
    /*check if we have a jump, cause they work diffrent

    /*print the opcode binary
    calculateOpcodeBinaryAndPrint(op_type, adTypeOper1, adTypeOper2, mode, IC,sym_table,label);
    /*print the opers binary
    calculateOperatorsBinaryAndPrint();
}

void calculateOpcodeBinaryAndPrint(OperatorType op_type, int adTypeOper1, int adTypeOper2, int mode, int *IC, Symbol *sy_table, char *label)
{
    bool needToPrintLabel = FALSE;
    char binary[15];
    strcpy(binary, "00000000000000\0");
    char temp[5];
    strcpy(temp, "0000\0");
    /*first, the opcode 8-10
    intToBinary(temp, (int)op_type);
    strcpy(binary + 4, temp);
    strcpy(temp, "0000\0");

    /*2-3 dst operand
    intToBinary(temp, adTypeOper2);
    strcpy(binary + 9, temp + 2);
    strcpy(temp, "0000\0");
    /*4-5 dst operand
    intToBinary(temp, adTypeOper1);
    strcpy(binary + 7, temp + 2);
    strcpy(temp, "0000\0");
    /*10-13 is for only address type 2 JMPS
    if (op_type == JMP || op_type == JSR || op_type == BNE)
    {
        /*first 12-13
        if (adTypeOper1 == 2)
            strcpy(binary, "11");
        else if (adTypeOper1 == 3)
            strcpy(binary, "01");
        /*first 10-11
        if (adTypeOper1 == 2)
            strcpy(binary + 2, "11");
        else if (adTypeOper1 == 3)
            strcpy(binary + 2, "01");
        needToPrintLabel = TRUE;
    } /*to do-ARE for operands

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
*/
/*
    input: a string and the number of steps back to take every item
*/
void rollBack(char *binary, int steps)
{
    int size = strlen(binary);
    int i, j;
    char temp;
    for (i = 0; i < size; i++)
    {

        j = (i - steps + size) % size;

        temp = binary[i];
        binary[i] = binary[j];
        binary[j] = temp;
    }
}
/*
    input: the string of the operand, the type of the operator, the mode and the symbol table
    output: the address type, per page 19
*/
int checkAddressType(char *oper, OperatorType opcode, int mode, Symbol *sym_table)
{
    char *bit = oper;
    if (*bit == '#')
        return 0;

    if (opcode == JMP || opcode == BNE || opcode == JSR)
        return 2;

    if (realRegister(oper) != -1)
        return 3;

    if (mode == SIMULATION || (mode != SIMULATION && existInSymbolTable(oper, sym_table) != -1))
        return 1;
    return -1;
}

/*
    input: the string for the operator that we recieved and a placeholder for the next
    output: the number of operands we have if we need to split the operands
*/
int breakDownJumps(char *oper1, char *oper2)
{
    /*if this a normal jump, will be not split because it has a label, else split to two operands */
    bool turn_to_second_oper = FALSE;
    char *bit = oper1;
    if (*bit == '(')
        bit++;

    int i = 0, j = 0;
    while (*bit != '\n')
    {
        if (*bit == ',')
        {
            bit++;
            oper1[i] = '\0';
            turn_to_second_oper = TRUE;
            continue;
        }

        if (!turn_to_second_oper)
        {
            oper1[i] = *bit;
            i++;
        }
        else
        {
            oper2[j] = *bit;
            j++;
        }

        bit++;
    }
    if (j > 0)
    {
        if (oper2[j - 1] == ')')
            j--;
        oper2[j] = '\0';
    }
    return turn_to_second_oper ? 2 : 1;
}