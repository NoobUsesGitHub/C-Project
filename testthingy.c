#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"

Operator *createOperatorsTable()
{
  int j = 0;
  Operator *op_table = (Operator *)malloc(OPERATORS_AMOUNT * sizeof(Operator));
  /* Populate the table: */
  Operator mov =
      {
          .type = MOV,
          .num_of_operands = 2,
          .src_addressing_methods = {0, 1, 2, 3},
          .dst_addressing_methods = {1, 2, 3, -1}};
  memcpy(op_table + MOV, &mov, sizeof(Operator));
  printf("Printing mov struct:\n");
  printf("type=%d, num_of_ops=%d\n", op_table[MOV].type, op_table[MOV].num_of_operands);
  printf("src arr:\n");
  for (j = 0; j < 4; j++)
  {
    printf("%d ", op_table[MOV].src_addressing_methods[j]);
  }
  printf("\ndst arr:\n");
  for (j = 0; j < 4; j++)
  {
    printf("%d ", op_table[MOV].dst_addressing_methods[j]);
  }
  return NULL;

  // /* mov */
  // op_table[MOV].type = MOV;
  // op_table[MOV].num_of_operands = 2;
  // op_table[MOV].src_addressing_methods = {0,1,2,3};

  // Operator cmp =
  // {
  //     .type = CMP,
  //     .num_of_operands = 2,
  //     .src_addressing_methods = {0,1,2,3},
  //     .dst_addressing_methods = {0,1,2,3}
  // };
  // for ( i = 0; i < OPERATORS_AMOUNT; i++)
  // {
  //     op_table[i] =
  // }
  // */
}

int main()
{
  Operator *ops_table = createOperatorsTable();
  return 0;
}
