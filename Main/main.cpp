// #include "mbed.h"
#include <stdio.h>

#define ON 1
#define OFF 0
#define DIGITS_NUM 3
#define NUM_PATTERN 10
#define SEGMENT_NUM 7

int* exchange_NUMtoARY(int num);
double powpow(int a, int b);
int* split_Numerical_Pos(double tmp, int beginning, int end);
void array_maker(double tmp, int* toInput, int beginning, int end);
void input_inteder_ary(int* fromSplit, int toOutput[DIGITS_NUM][SEGMENT_NUM], int digits);

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

void print_array(int src[3][7]){
  for(int i = 0; i < 3; i++){
    for (int j = 0; j < 7; j++) printf("%d ", src[i][j]);
    putchar('\n');
  }
}

void put_line(void){
  for (int i = 0; i < 20; i++) putchar('-');
  putchar('\n');
}

int main(void){
  
  double tmp = 23.5;
  int splited_tmp[DIGITS_NUM];
  int temperature_ary[DIGITS_NUM][SEGMENT_NUM];

  int count = 340;
  int splited_cnt[DIGITS_NUM];
  int count_ary[DIGITS_NUM][SEGMENT_NUM];

  array_maker(tmp, splited_tmp, 1, -1);
  input_inteder_ary(splited_tmp, temperature_ary, DIGITS_NUM);
  
  array_maker(count, splited_cnt, 2, 0);
  input_inteder_ary(splited_cnt, count_ary, DIGITS_NUM);

  put_line();
  print_array(temperature_ary);
  put_line();
  print_array(count_ary);
  put_line();
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

int* split_Numerical_Pos(double tmp, int beginning, int end){
  const int width = beginning - end + 1;
  int ary[width];
  int* dest_num = ary;
  int  i, j, k = 0;
  
  tmp += 0.05; 
    for (i = beginning; i > (end-1); i--){ 
    for (j = 0; tmp >= powpow(10, i); j++) tmp -=powpow(10, i);
    ary[k] = j;
    k++;
  }
  return dest_num;
}

void array_maker(double tmp, int* toInput, int beginning, int end){
  const int width = beginning - end;
  for (int i = 0; i < width; i++) toInput[i] = split_Numerical_Pos(tmp, beginning, end)[i];
}

void input_inteder_ary(int* splited_num, int segment_array[DIGITS_NUM][SEGMENT_NUM], int digits){
  for (int i = 0; i < digits; i++)
    for (int j = 0; j < SEGMENT_NUM; j++)
      segment_array[i][j] = exchange_NUMtoARY(splited_num[i])[j];
}
