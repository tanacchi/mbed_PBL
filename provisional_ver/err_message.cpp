#include <stdio.h>

#define ON 1
#define OFF 0


void err_message();
  
int main(){



  return 0;
}

void err_message(){
  int error_array[3][7] = {
    {ON,  OFF, OFF, ON,  ON, ON,  ON},
    {OFF, OFF, OFF, OFF, ON, OFF, ON},
    {OFF, OFF, OFF, OFF, ON, OFF, ON}
  }  
  digits_init();
  for (int i = 0; i < WIDTH; i++){
    digit[i] = 0;
    output_digit(error_array[i]);
    wait(0.01);
  }
}
