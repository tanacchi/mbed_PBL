// #include "mbed.h"
#include <stdio.h>
#include <sstream>
#include <cstdlib>
#include <stdlib.h>

#define ON 1
#define OFF 0

int* exchange_NUMtoARY(int num);
double powpow(int a, int b);
int* split_Numerical_Pos(double dd);
void array_maker(double dd, int* src);
void input_integer_ary(int* fromsplt, int **toOuntput);

int sevseg_ary[10][7] = {
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

  // class Thermometor{
  // private:
  //   double sensor_gets;
  //   int splited_num[3];
  //   int segment_array[3][7];
  // public:
  //   array_maker(double dd);
  //   exchange_NUMtoARY();
  // }
  
  int i, j;
  double dd = 91.7;
  int splited_num[3] = {};
  int segment_array[3][7] = {};
  void input_inteder_ary(int* fromSplit, int **toOutput);
  
  for (i = 0; i < 3; i++)
    splited_num[i] = split_Numerical_Pos(dd)[i];
  
  // array_maker(dd, splited_num);
  
  for (i = 0; i < 3; i++){
    for (j = 0; j < 7; j++)
      segment_array[i][j] = exchange_NUMtoARY(splited_num[i])[j];

    // input_integer_ary(splited_num, segment_array);
  
    // for (i = 0; i < 3; i++){
    //   for (j = 0; j < 7; j++)
    //     printf("%d  ", segment_array[i][j]);
    //   putchar('\n');
    //}

    for (i = 0; i < 3; i++){
      for (j = 0; j < 7; j++)
        printf("%d  ",segment_array[i][j]);
      putchar('\n');
    } 
      putchar('\n');
  }
}

int* exchange_NUMtoARY(int num){
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

  void array_maker(double dd, int* toInput){
    int i;
    for (i = 0; i < 3; i++) toInput[i] = split_Numerical_Pos(dd)[i];
  }

  void input_inteder_ary(int* fromSplit, int** toOutput){
    int i, j;
    for (i = 0; i < 3; i++)
      for (j  = 0; j < 7; j++)
        toOutput[i][j] = exchange_NUMtoARY(fromSplit[i])[j];
  }
