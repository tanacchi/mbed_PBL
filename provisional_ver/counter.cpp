#include <stdio.h>

int counter(void);

int main(void){
  
  while (1)
    printf("%d\n", counter());
  
  return 0;
}

int counter(void){
  static int num;
  num++;
  return num;
}
