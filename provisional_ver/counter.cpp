#include <stdio.h>

int counter(void);
void wait(int milisec);

int main(void){
  
  while (1){
    printf("%d\n", counter());
    wait(300);
  }
  
  return 0;
}

int counter(void){
  static int num;
  if (num > 999) num = 0; 
  return num++;
}

void wait(int milisec){
  for (int i = 0; i < milisec*10000; i++);
}
