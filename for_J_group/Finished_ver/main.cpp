// #include "mbed.h"
#include <stdio.h>

#define ON 1
#define OFF 0
#define SEGMENT_NUM 7
#define NUM_PATTERN 10

int* exchange_NUMtoARY(int num);
double powpow(int a, int b);
int* split_Numerical_Pos(double tmp);
void array_maker(double tmp, int* toInput);
void input_inteder_ary(int* fromSplit, int toOutput[3][SEGMENT_NUM]);

int sevseg_ary[NUM_PATTERN][SEGMENT_NUM] = {
  {ON,  ON,  ON,  ON,  ON,  ON , OFF}, // for 0
  {OFF, ON,  ON,  OFF, OFF, OFF, OFF}, // for 1
  {ON,  ON,  OFF, ON,  ON,  OFF, ON }, // for 2
  {ON,  ON,  ON,  ON,  OFF, OFF, ON }, // for 3
  {OFF, ON , ON,  OFF, OFF, ON,  ON }, // for 4
  {ON,  OFF, ON,  ON,  OFF, ON , ON }, // for 5
  {ON,  OFF, ON,  ON,  ON,  ON,  ON }, // for 6
  {ON,  ON,  ON,  OFF, OFF, OFF, OFF}, // for 7
  {ON,  ON,  ON,  ON,  ON,  ON,  ON }, // for 8
  {ON,  ON,  ON,  ON,  OFF, ON,  ON }  // for 9
};

int main(void){
  
  double tmp = 11.1;
  int splited_num[3];
  int segment_array[3][SEGMENT_NUM];
  
  array_maker(tmp, splited_num);
  input_inteder_ary(splited_num, segment_array);

  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 7; j++) printf("%d ", segment_array[i][j]);
      putchar('\n');
  }
}

int* exchange_NUMtoARY(int num){
  return sevseg_ary[num];
}

double powpow(int a, int b){
  double dest = 1;
  
  if (b > 0)
    for (int i = 0; i < b; i++) dest *= (double)a;
  if (b < 0)
    for (int i = 0; i > b; i--) dest /= (double)a;

  return dest;
}

int* split_Numerical_Pos(double tmp){
  int ary[3];
  int* dest = ary;
  int i, j, k = 0;
  
  tmp += 0.05; 
  
  for (i = 1; i > -2; i--){ 
    for (j = 0; tmp >= powpow(10, i); j++) tmp -=powpow(10, i);
    ary[k] = j;
    k++;
  }
  return dest;
}

void array_maker(double tmp, int* toInput){
  for (int i = 0; i < 3; i++) toInput[i] = split_Numerical_Pos(tmp)[i];
}

void input_inteder_ary(int* splited_num, int segment_array[3][SEGMENT_NUM]){
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < SEGMENT_NUM; j++)
      segment_array[i][j] = exchange_NUMtoARY(splited_num[i])[j];
}
