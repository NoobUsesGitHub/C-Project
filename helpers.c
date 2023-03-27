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
void dumpDataOpers(char *str, int *cnt, int mode,FILE* fp)
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
                printf("%d  %s", *cnt, binaryChar);
            *cnt++;
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
            printf("%d  %s", *cnt, binaryChar);
        *cnt=*cnt+1;
        clearStr(temp, size);
        *cnt=*cnt+1;
    }
}

/*
    input: a string and the Data counter
    will print the individual letters as binary and increase the DC
*/
void dumpStr(char *oper, int *cnt, int mode,FILE *fp)
{
    int size = strlen(oper);
    char binaryChar[14];
    int value;
    while (*oper != '\0' && *oper != '\n')
    {
        value = (int)(*oper);
        intToBinary(binaryChar, value);
        if (mode != SIMULATION)
            printf("%d  %s", *cnt, binaryChar);
        *cnt++;
        oper++;
    }
    printf("%d  %s", *cnt, binaryChar);
    *cnt++;
}

/*
    input: a placeholder string and a number to change to binary
    will leave the number in binary (in 12 bits) in the placeholder str
*/
void intToBinary(char *binaryChar, int value)
{
    char temp;
    int bufferSize = strlen(binaryChar);
    int i = 0;
    for (i = bufferSize - 1; i >= 0; i--)
    {
        if ((value >> i) & 1)
        {
            binaryChar[i] = '1';
        }
        else
        {
            binaryChar[i] = '0';
        }
    }

    bufferSize = strlen(binaryChar);
    i = 0;
    for (; i < bufferSize / 2; i++)
    {
        temp = binaryChar[i];
        binaryChar[i] = binaryChar[bufferSize - i - 1];
        binaryChar[bufferSize - i - 1] = temp;
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

/*
    not done yet
    general Idea- will recieve label, opcode,operator1 operator2 and then code them up to binary

*/

void dumpFullInstruction(char *label, char *opcode, char *oper1, char *oper2, int opersCnt, int *IC, int mode, Operator *op_table, Symbol *sym_list)
{
    int adTypeOper1 = 0, adTypeOper2 = 0;
    OperatorType op_type = stringToOperatorType(opcode);
    if (opersCnt != getNumOfOperands(op_type, op_table)) /*do we have more than required operators*/
        printf(stderr, "opcode %s has more operators than expected", opcode);

    /*take the types of two opers*/

    adTypeOper1 = checkAddressType(oper1, op_type, mode, sym_list);
    adTypeOper2 = checkAddressType(oper2, op_type, mode, sym_list);
    if (!isAddTypeCorrect(op_type, adTypeOper1, adTypeOper2, op_table))
    {
        fprintf(stderr, "incorrect address type for one of the operators for %s in %d", opcode, *IC);
        adTypeOper1 = 0;
        adTypeOper2 = 0; /*adding dummy info*/
    }

    if(mode==EXECUTION)
    {
        /*looking through for externals*/
        checkForExternals(oper1,line,sym_list);
        checkForExternals(oper2,sym_list);
    }

    /*print the opcode binary*/
    calculateOpcodeBinaryAndPrint(op_type, adTypeOper1, adTypeOper2, mode, IC, sym_list, label);
    /*print the opers binary*/
    calculateOperatorsBinaryAndPrint(oper1, oper2, adTypeOper1, adTypeOper2, mode, IC, sym_list);
}

void calculateOperatorsBinaryAndPrint(char *oper1, char *oper2, int adTypeOper1, int adTypeOper2, int mode, int *IC, Symbol *sym_list)
{
    char binary[15], temp[5];
    strcpy(binary, "00000000000000\0");
    strcpy(temp, "0000\0");

    if (adTypeOper1 == adTypeOper2 && adTypeOper2 == 3)
    {
        /*if both registers, we set them as one
        reg1+reg2+A(00)
        */
        intToBinary(binary, realRegister(oper1));
        intToBinary(binary, 7);

        intToBinary(temp, realRegister(oper2));
        strcpyBySteps(binary, temp + 2, 2);
        shiftLeftChar(binary, 2);
        if (mode != SIMULATION)
            printf("%d  %s", *IC, binary);
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
            strcpyBySteps(binary, temp + 2, 2);
            printf("%d  %s", *IC, binary);
            *IC = *IC + 1;
            break;

        case 1: /*label*/
        
            if (existInSymbolTable(oper1) != -1 && symbolTypeFromTable(oper1, sym_list) == EXTERN)
            {
                /*oper1+E(01)*/
                intToBinary(binary, existInSymbolTable(oper1, sym_list));
                shiftLeftChar(binary, 2);
                temp[3] = '1';
                temp[2] = '0';
                strcpyBySteps(binary, temp + 2, 2);
                if (mode != SIMULATION)
                    printf("%d  %s", *IC, binary);
                *IC = *IC + 1;
            }
            else
            {
                /*oper1+R(10)*/

                intToBinary(binary, existInSymbolTable(oper1, sym_list));
                shiftLeftChar(binary, 2);
                temp[3] = '0';
                temp[2] = '1';
                strcpyBySteps(binary, temp + 2, 2);
                if (mode != SIMULATION)
                    printf("%d  %s", *IC, binary);
                *IC = *IC + 1;
            }
            break;
        case 3: /*register*/
            /*regCode(oper1)+A(00) */
            intToBinary(binary, realRegister(oper1));
            shiftLeftChar(binary, 7);
            if (mode != SIMULATION)
                printf("%d  %s", *IC, binary);
            *IC = *IC + 1;
            break;
        }

        strcpy(binary, "00000000000000\0");
        strcpy(temp, "0000\0");
        switch (adTypeOper2)
        {
        case -1:
            break;

        case 0: /*number*/
            /*oper2 +A(00)*/
            intToBinary(binary, atoi(oper2 + 1));
            shiftLeftChar(binary, 2);
            strcpyBySteps(binary, temp + 2, 2);
            printf("%d  %s", *IC, binary);
            *IC = *IC + 1;
            break;

        case 1: /*label*/
            if (existInSymbolTable(oper2) != -1 && symbolTypeFromTable(oper2, sym_list) == EXTERN)
            {
                /*oper2+E(01)*/
                intToBinary(binary, existInSymbolTable(oper2, sym_list));
                shiftLeftChar(binary, 2);
                temp[3] = '1';
                temp[2] = '0';
                strcpyBySteps(binary, temp + 2, 2);
                if (mode != SIMULATION)
                    printf("%d  %s", *IC, binary);
                *IC = *IC + 1;
            }
            else
            {
                /*oper2+R(10)*/
                intToBinary(binary, existInSymbolTable(oper2, sym_list));
                shiftLeftChar(binary, 2);
                temp[3] = '0';
                temp[2] = '1';
                strcpyBySteps(binary, temp + 2, 2);
                if (mode != SIMULATION)
                    printf("%d  %s", *IC, binary);
                *IC = *IC + 1;
            }
            break;
        case 3: /*register*/
            /*regCode(oper2)+A(00) */
            intToBinary(binary, realRegister(oper2));
            shiftLeftChar(binary, 2);
            strcpyBySteps(binary, temp + 2, 2);
            if (mode != SIMULATION)
                printf("%d  %s", *IC, binary);
            *IC = *IC + 1;
            break;
        }
    }
}

/*
    input: the type of the operator, the address types of the operands, the mode, the instruction counter, the symbol info table and the label
    will turn the opcode to binary, if there is a label(aka we are jumping, will print that too)
*/
void calculateOpcodeBinaryAndPrint(OperatorType op_type, int adTypeOper1, int adTypeOper2, int mode, int *IC, Symbol *sy_list, char *label)
{
    bool needToPrintLabel = FALSE;
    char binary[15], temp[5];
    strcpy(binary, "00000000000000\0");
    strcpy(temp, "0000\0");

    /*first, the opcode 8-10*/
    intToBinary(temp, (int)op_type);
    strcpyBySteps(binary + 4, temp, 4);
    strcpy(temp, "0000\0");

    /*2-3 dst operand*/
    if (adTypeOper2 != -1)
    {
        intToBinary(temp, adTypeOper2);
        strcpyBySteps(binary + 10, temp + 2, 2);
        strcpy(temp, "0000\0");
    }
    /*4-5 src operand*/
    if (adTypeOper1 != -1)
    {
        intToBinary(temp, adTypeOper1);
        strcpyBySteps(binary + 8, temp + 2, 2);
        strcpy(temp, "0000\0");
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
        printf("%d  %s\n", *IC, binary);
    *IC = *IC + 1;
    strcpy(binary, "00000000000000\0");
    if (needToPrintLabel)
    {
        intToBinary(binary, existInSymbolTable(label, sy_list));
        shiftLeftChar(binary, 2);
        strcpy(binary + 12, "10");
        if (mode != SIMULATION)
            printf("%d  %s", *IC, binary);
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
    char temp[size];
    memset(temp, '0', size);
    int i = steps, j = 0;
    while (i < size)
    {
        temp[j] = binary[i];
        i++;
        j++;
    }
    memcpy(binary, temp, (size + 1) * sizeof(char));
    binary[size + 1] = '\0';
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

    if (opcode == JMP || opcode == BNE || opcode == JSR)
        return 2;

    if (realRegister(oper) != -1)
        return 3;

    if (mode == SIMULATION || (mode != SIMULATION && existInSymbolTable(oper, sym_list) != -1))
        return 1;
    return -1;
}

/*
    input: the string for the operator that we recieved and a placeholder for the next and the label
    output: the number of operands we have if we need to split the operands and label
*/
int breakDownJumps(char *oper1, char *oper2, char label)
{
    /*if this a normal jump, will be not split because it has a label, else split to two operands */
    bool turn_to_second_oper = FALSE;
    char *bit = oper1;
    char *label_pointer = label;
    memset(label, '\0', MAX_LABEL_SIZE * sizeof(char));
    /*collecting a label, we have one for sure*/
    while (*bit != '(' && *bit != '\n')
    {
        *label_pointer = *bit;
        bit++;
        label_pointer++;
    }
    /*checking if we have operands*/
    if (*bit == '(')
        bit++;
    else
        return 1;

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

/*
    input: a header of the symbols table, the file name, a data symbol type, and the extention
    will push all the data symbols of that type to a file
*/
void dumpSymbols(Symbols *header, char *fileName, Stype stype, char *extention)
{
    char newName[strlen(fileName)];
    char binary[15];
    bool found_any = FALSE;
    char *bit = NULL;
    strcpy(binary, "00000000000000\0");
    strcpy(newName, fileName);
    strcpyBySteps(newName + strlen(newName) - strlen(extention), extention, 3);
    FILE *fp = fopen(newName, "w");
    if (fp == NULL)
        fprintf(stderr, "we had trouble opening a %s file", extention);
    while (header->next != NULL)
    {
        if (header->type == stype||(header->externalType == stype&&header->externalType ==CODE))
        {
            found_any = TRUE;
            intToBinary(binary, header->line);
            bit = binary;
            while (*bit != '\0')
            {
                *bit = binaryTranslate(*bit);
                bit++;
            }
            fprintf(fp, "%s  %s\n", header->name, binary);
            strcpy(binary, "00000000000000\0");
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
void dumpSymbolsToMainFile(Symbol *header, int IC, FILE *fp)
{
    int numOfSymbols = countSymbols(header), i = 0;
    Symbol* arr[numOfSymbols];
    fillSymArr(arr, numOfSymbols, header);
    qsort(arr,numOfSymbols,sizeof(Symbol),SymbolCompare);

    for(;i<numOfSymbols;i++)
    {
        switch (arr[i]->type)
        {
        case STRING:
            dumpStr(arr[i]->input, &IC, EXECUTION,fp);
            break;
        
        case DATA:
            dumpDataOpers(arr[i]->input, &IC, EXECUTION,fp);
            break;
        }
    }
}


/*
    input: the string name, it's line and the symbol list header
    if it exists, will update the symbol list with external symbol if it exists 
*/
void checkForExternals(char* oper,int line,Symbol* sym_list)
{
    if(symbolTypeFromTable(oper,sym_list)==EXTERN)
    {
        addSymbolToList(sym_list,oper,EXTERN,line,NULL);
    }

}