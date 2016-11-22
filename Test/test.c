#include <stdio.h>

#define ON 1
#define OFF 0

int* exchange_NUMtoARY(int num){

  int* dest;
 const int sev_seg_ary[10][7] = {
    {ON,  ON,  ON,  ON,  ON,  ON , OFF},
    {OFF, ON,  ON,  OFF, OFF, OFF, OFF},
    {ON,  ON,  OFF, ON,  ON,  OFF, ON },
    {ON,  ON,  ON,  ON,  OFF, OFF, ON },
    {OFF, ON , ON,  OFF, OFF, ON,  ON },
    {ON,  OFF, ON,  ON,  ON,  OFF, ON },
    {ON,  OFF, ON,  ON,  ON,  ON,  ON },
    {ON,  ON,  ON,  OFF, OFF, OFF, OFF},
    {ON,  ON,  ON,  ON,  ON,  ON,  ON },
    {ON,  ON,  ON,  ON,  OFF, ON,  ON }
  };

  return dest = sev_seg_ary[num];
}

int main(void){

  int array[7];

  int i, j;
  char ONOFF[70];
 
  for (j = 0; j < 10; j++){
    for (i = 0; i < 7; i++)
      array[i] = exchange_NUMtoARY(1)[i];
    
    for (i = 0; i < 7; i++){
      if (array[i] == 1)
        printf("ON,  ");
      else
        printf("OFF, ");
    }
    putchar('\n');
  }
  
  return 0;
}
