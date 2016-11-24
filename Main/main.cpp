// #include "mbed.h"
#include <stdio.h>

#define ON 1
#define OFF 0

int* exchange_NUMtoARY(int num);
double powpow(int a, int b);
int* split_Numerical_Pos(double dd);

int sevseg_ary[10][7] = {
    {ON,  ON,  ON,  ON,  ON,  ON , OFF}, 
    {OFF, ON,  ON,  OFF, OFF, OFF, OFF}, 
    {ON,  ON,  OFF, ON,  ON,  OFF, ON }, 
    {ON,  ON,  ON,  ON,  OFF, OFF, ON }, 
    {OFF, ON , ON,  OFF, OFF, ON,  ON }, 
    {ON,  OFF, ON,  ON,  OFF,  ON , ON }, 
    {ON,  OFF, ON,  ON,  ON,  ON,  ON }, 
    {ON,  ON,  ON,  OFF, OFF, OFF, OFF}, 
    {ON,  ON,  ON,  ON,  ON,  ON,  ON }, 
    {ON,  ON,  ON,  ON,  OFF, ON,  ON }  
  };
  
int main(void){

  int test_array[3] = {};
  int splited_num;
  int segment_array[7];
  int i, j;
  
  for (i = 0; i < 3; i++)
    test_array[i] = split_Numerical_Pos(23.5)[i];

  for (i = 0; i < 3; i++){
    for (j = 0; j < 7; j++)
      segment_array[j] = exchange_NUMtoARY(test_array[i])[j];
    for (j = 0; j < 7; j++)
      printf("%d  ", segment_array[j]);
    putchar('\n');
  }
}

int* exchange_NUMtoARY(int num){  // exchange_NUMtoARY(num)[i]

  int* dest;
  return dest = sevseg_ary[num];
}

double powpow(int a, int b){
  double dest = 1;
  int i;
  
  if (b > 0)
    for (i = 0; i < b; i++) dest *= (double)a;
  if (b < 0)
    for (i = 0; i > b; i--) dest /= (double)a;
  
  return dest;
}

int* split_Numerical_Pos(double dd){ 
  int ary[3] = {};
  int *dest_num = ary;
  int  i, j;

  dd += 0.05; 
  
  for (i = 1; i > -2; i--){ 
    for (j = 0; dd >= powpow(10, i); j++) 
      dd -=powpow(10, i);
    ary[1-i] = j;
  }
  return dest_num;
}
