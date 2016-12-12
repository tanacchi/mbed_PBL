#include "mbed.h"

#define MBED_VOLTAGE 3.3

#define ON 1
#define OFF 0
#define SEGMENT_NUM 7
#define NUM_PATTERN 10

#define TMP_SENSOR_PIN p20

#define SEGMENT_A p10
#define SEGMENT_B p11
#define SEGMENT_C p12
#define SEGMENT_D p13
#define SEGMENT_E p14
#define SEGMENT_F p15
#define SEGMENT_G p16

#define DIG_1_PIN p21
#define DIG_2_PIN p22
#define DIG_3_PIN p23

#define WIDTH 3

DigitalOut segment[7] = {
  DigitalOut (SEGMENT_A),
  DigitalOut (SEGMENT_B),
  DigitalOut (SEGMENT_C),
  DigitalOut (SEGMENT_D),
  DigitalOut (SEGMENT_E),
  DigitalOut (SEGMENT_F),
  DigitalOut (SEGMENT_G)
};

DigitalOut digit[3] = {
  DigitalOut (DIG_1_PIN),
  DigitalOut (DIG_2_PIN),
  DigitalOut (DIG_3_PIN)
};

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

class sevseg_LED{
  int head, tale;
  double input_number;
  int splited_num[WIDTH];
  int output_array[WIDTH][SEGMENT_NUM]; 
public:
  sevseg_LED(int head);
  void set_number(double num);
  void split_Numerical_Pos();
  void input_inteder_ary();
  void output_console();
  void output_sevseg();
};

double powpow(int a, int b);
double get_Temperature(void);
void digits_init();
int* exchange_NUMtoARY(int element);
void output_digit(int out_digit[SEGMENT_NUM]);    
void Thermometer();
void Stop_watch();
double minute_counter();

int main(void){
  Stop_watch();
  
  return 0;
}

void Thermometer(){

  double data;
  sevseg_LED tmp(1);

  while (1){
    // data = get_Temperature();
    tmp.set_number(data);
    tmp.split_Numerical_Pos();
    tmp.input_inteder_ary();
    tmp.output_sevseg();
  }
}

void Stop_watch(){
  
  double data;
  sevseg_LED time(1);
  
  while (1){
    data = minute_counter();
    time.set_number(data);
    time.split_Numerical_Pos();
    time.input_inteder_ary();
    time.output_sevseg();
  }
}

double minute_counter(){
  static double milinum;
  milinum += 0.1;
  if (milinum > 999) milinum = 0;
  return milinum / 10;
}

// double get_Temperature(void){
//   AnalogIn mysensor(TMP_SENSOR_PIN);
//   double replyed_vol  = mysensor * MBED_VOLTAGE;
//   return replyed_vol * 100;
// }

double powpow(int a, int b){
  double dest = 1;
  if (b > 0) for (int i = 0; i < b; i++) dest *= (double)a;
  if (b < 0) for (int i = 0; i > b; i--) dest /= (double)a;
  
  return dest;
}

int* exchange_NUMtoARY(int element){
  return sevseg_ary[element];
}

void digits_init(){
  for (int i = 0; i < WIDTH; i++) digit[i] = 1;
}

void output_digit(int out_digit[SEGMENT_NUM]){
  for (int i = 0; i < SEGMENT_NUM; i++)
    segment[i] = out_digit[i];  
}

sevseg_LED::sevseg_LED(int input_head){ // head < tale　-> Err!!
  head = input_head;
  tale = head - WIDTH;
}

void sevseg_LED::set_number(double num){
  input_number = num;
}

void sevseg_LED::split_Numerical_Pos(){
  int i, j, k = 0;
  for (i = head; i > tale-1; i--){ 
    for (j = 0; input_number >= powpow(10, i); j++) input_number -=powpow(10, i);
    splited_num[k++] = j;
  }
}

void sevseg_LED::input_inteder_ary(){
  for (int i = 0; i < WIDTH; i++)
    for (int j = 0; j < SEGMENT_NUM; j++)
      output_array[i][j] = exchange_NUMtoARY(splited_num[i])[j];
}

void sevseg_LED::output_sevseg(){ 
   for (int i = 0; i < WIDTH; i++){
     digits_init();
     digit[i] = 0;
     output_digit(output_array[i]);
     wait(0.001);
   }
}
