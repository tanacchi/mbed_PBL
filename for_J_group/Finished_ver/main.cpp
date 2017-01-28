#include "mbed.h"

#define MBED_VOLTAGE 3.3

#define ON 1
#define OFF 0

#define SEGMENT_NUM 7
#define DIGITS_NUM 4
#define NUM_PATTERN 10
#define SEVSEG_WIDTH 4

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
#define DIG_4_PIN p24

DigitalOut segment[SEGMENT_NUM] = {
  DigitalOut (SEGMENT_A),
  DigitalOut (SEGMENT_B),
  DigitalOut (SEGMENT_C),
  DigitalOut (SEGMENT_D),
  DigitalOut (SEGMENT_E),
  DigitalOut (SEGMENT_F),
  DigitalOut (SEGMENT_G)
};

DigitalOut digit[DIGITS_NUM] = {
  DigitalOut (DIG_1_PIN),
  DigitalOut (DIG_2_PIN),
  DigitalOut (DIG_3_PIN),
  DigitalOut (DIG_4_PIN)
};

class sevseg_LED {
  int head, tale;
  int input_number;
  int splited_num[SEVSEG_WIDTH];
  int inteder_array[SEVSEG_WIDTH][SEGMENT_NUM]; 
public:
  sevseg_LED(int head);
  void set_number(int num);
  void split_Numerical_Pos();
  void input_inteder_ary();
  void output_console();
  void output_sevseg();
};

void sevseg_Clock();
int get_time(int count);
int powpow(int a, int b);
int* convert_NUMintoARY(int element);
void digits_init();
void output_digit(int out_digit[SEGMENT_NUM]);
void output_array(int inteder_array[DIGITS_NUM][SEGMENT_NUM]);
void Err_message();

int main() {
  sevseg_Clock();
  return 0;
}

void sevseg_Clock() {
  int data = 180;
  sevseg_LED time(3);
  while (1){
    data = get_time(data);
    time.set_number(data);
    time.split_Numerical_Pos();
    time.input_inteder_ary();
    time.output_sevseg();
  }
}

int get_time(int param) {
  static int count;
  if (count++ > 500) count = 0;
  if (count) param--;
  return param;
}

sevseg_LED::sevseg_LED(int input_head) {
  head = input_head;
  tale = head - SEVSEG_WIDTH;
}

void sevseg_LED::set_number(int num) {
  input_number = num;
}

void sevseg_LED::split_Numerical_Pos() {
  int i, j, k = 0;
  for (i = head; i > tale; i--){
    for (j = 0; input_number >= powpow(10, i); j++) input_number -= powpow(10, i);
    splited_num[k++] = j;
  }
}

void sevseg_LED::input_inteder_ary() {
  for (int i = 0; i < SEVSEG_WIDTH; i++)
    for (int j = 0; j < SEGMENT_NUM; j++)
      inteder_array[i][j] = convert_NUMintoARY(splited_num[i])[j];
}

void sevseg_LED::output_sevseg() {
  output_array(inteder_arrary);
}

int powpow(int a, int b) {
  int dest = 1;
  if (b > 0) for (int i = 0; i < b; i++) dest *= a;
  if (b < 0) for (int i = 0; i > b; i--) dest /= a;
  return dest;
}

int* convert_NUMintoARY(int element) {
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
  if (element < 0 || 9 < element) Err_message();
  return sevseg_ary[element];
}

void digits_init() {
  for (int i = 0; i < SEVSEG_WIDTH; i++) digit[i] = 1;
}

void output_digit(int out_digit[SEGMENT_NUM]) {
  for (int i = 0; i < SEGMENT_NUM; i++)
    segment[i] = out_digit[i];  
}

void output_array(int inteder_array[DIGITS_NUM][SEGMENT_NUM]) {
  for (int i = 0; i < SEVSEG_WIDTH; i++){
    digits_init();
    digit[i] = 0;
    output_digit(output_array[i]);
    wait(0.001);
  }
}

void Err_message() {
  int error_array[DIGITS_NUM][SEGMENT_NUM] = {
    {ON,  OFF, OFF, ON,  ON, ON,  ON},
    {OFF, OFF, OFF, OFF, ON, OFF, ON},
    {OFF, OFF, ON,  ON,  ON, OFF, ON},
    {OFF, OFF, OFF, OFF, ON, OFF, ON}
  };
  while (1) output_array(error_array);
}
