#include <stdio.h>

double powpow(int a, int b){
  double dest = 1;
  int i;
  
  if (b > 0)
    for (i = 0; i < b; i++) dest *= (double)a;
  else if (b < 0)
    for (i = 0; i < -b; i++) dest /= (double)a;
  else dest = 1;
  
  return dest;
}

int* split_Numerical_Pos(double dd){
  int ary[3] = {};
  int *dest_num = ary;
  int  i, j;

  dd += 0.05;
  
  for (i = 1; i > -2; i--){ 
    for (j = 0; dd >= powpow(10, i); j++){ 
      dd -=powpow(10, i);
    }
    ary[1-i] = j;
  }
  return dest_num;
}

int main(void){

  int i;
  for (i = 0; i < 3; i++){
    if (i == 2) putchar('.');
    printf("%d", split_Numerical_Pos(23.48)[i]);
  }
  putchar('\n');
  
  return 0;
}
