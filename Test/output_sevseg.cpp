#include "mbed.h"

DigitalOut a(p10);
DigitalOut b(p11);
DigitalOut c(p12);
DigitalOut d(p13);
DigitalOut e(p14);
DigitalOut f(p15);
DigitalOut g(p16);

DigitalOut dig1(p21);
DigitalOut dig2(p22);
DigitalOut dig3(p23);

void input_array(int number);
void output_7seg(int* array);
  
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


int main(){

  int n1;
  int n2;
  int n3;
  int num;

  int i = 1;

  while (1){
    if (i == 1){
      dig1 = 0;
      dig2 = 1;
      dig3 = 1;
      num = n1;
    }
    if (i == 2){
      dig1 = 1;
      dig2 = 0;
      dig3 = 1;
      num = n2;
    }
    if (i == 3){
      dig1 = 1;
      dig2 = 1;
      dig3 = 0;
      num = n3;
    }

     // input_array(num);

    if (num == 0){a=1; b=1; c=1; d=1; e=1; f=1; g=0;}
    if (num == 1){a=0; b=1; c=1; d=0; e=0; f=0; g=0;}
    if (num == 2){a=1; b=1; c=0; d=1; e=1; f=0; g=1;}   
    if (num == 3){a=1; b=1; c=1; d=1; e=0; f=0; g=1;}
    if (num == 4){a=0; b=1; c=1; d=0; e=0; f=1; g=1;}
    if (num == 5){a=1; b=0; c=1; d=1; e=0; f=1; g=1;}
    if (num == 6){a=1; b=0; c=1; d=1; e=1; f=1; g=1;}
    if (num == 7){a=1; b=1; c=1; d=0; e=0; f=0; g=0;}
    if (num == 8){a=1; b=1; c=1; d=1; e=1; f=1; g=1;}
    if (num == 9){a=1; b=1; c=1; d=1; e=0; f=1; g=1;}
    wait(0.001);

    i++;
    if (i == 4) i = 1;  
  }

}

void input_array(int number){
  a = sevseg_array[number][0];
  b = sevseg_array[number][1];
  c = sevseg_array[number][2];
  d = sevseg_array[number][3];
  e = sevseg_array[number][4];
  f = sevseg_array[number][5];
  g = sevseg_array[number][6];
}


void output_7seg(int* array){
  ;
}
