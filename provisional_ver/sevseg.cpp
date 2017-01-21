// ------------------------- Include files -------------------------------------

#include "mbed.h"

// ------------------------- Definition ----------------------------------------

#define MBED_VOLTAGE 3.3

#define ON 1
#define OFF 0
#define SEGMENT_NUM 7
#define DIGITS_NUM 3
#define NUM_PATTERN 10
#define MBED_LED_NUM 4
#define WAIT_NUM 5

#define SEGMENT_A p10
#define SEGMENT_B p11
#define SEGMENT_C p12
#define SEGMENT_D p13
#define SEGMENT_E p14
#define SEGMENT_F p15
#define SEGMENT_G p16
#define SEG_POINT p17

#define SWITCH_R p18
#define SWITCH_L p19

#define TMP_SENSOR_PIN p20

#define DIG_1_PIN p21
#define DIG_2_PIN p22
#define DIG_3_PIN p23

// ------------------------- Global variable -----------------------------------

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
  DigitalOut (DIG_3_PIN)
};

DigitalOut digit_point(SEG_POINT);

// ------------------------- 7 segment LED class -------------------------------

class sevseg_LED {
  int head, tale;
  int point;
  double src_number;
  int splited_num[DIGITS_NUM];
  int inteder_ary[DIGITS_NUM][SEGMENT_NUM];
public:
  sevseg_LED(int head);
  void set_number(double input_num);
  void split_Numerical_Pos();
  void input_inteder_ary();
  void output_console();
  void output_sevseg();
  void set_digit_point(int i);
};

// ------------------------- Function prototype --------------------------------

int switch_reader(int ch);
int mode_reader();
void wait_switch_left();
int starter_switch();
int mode_switcher();
int split_count(int count, int maximam);
void Thermometer();
double get_Temperature();
double tmp_stopper();
void Counter();
int count_stopper(int current_push);
int change_param(int counter);
double powpow(int a, int b);
int* convert_NUMintoARY(int element);
void digits_init();
void mbedLED_init();
void output_digit(int out_digit[SEGMENT_NUM]);
void output_array(int inteder_array[DIGITS_NUM][SEGMENT_NUM]);
void disp_limit_sevseg(int lim);
void disp_limit_LED(int lim);
void Err_message();

// -------------------------- Thermometer --------------------------------------

void Thermometer() {
  double data = get_Temperature();
  sevseg_LED tmp(1);

  while (mode_switcher()) {
    data = tmp_stopper();
    tmp.set_number(data);
    tmp.split_Numerical_Pos();
    tmp.input_inteder_ary();
    tmp.output_sevseg();
  }
}

// ------------------------- Output 7 segment LED (member function) ------------

sevseg_LED::sevseg_LED(int input_head) {
  head = input_head;
  point = head;
  tale = head - DIGITS_NUM;
}

void sevseg_LED::set_number(double input_num) {
  src_number = input_num;
}

void sevseg_LED::split_Numerical_Pos() {
  int i, j, k = 0;
  for (i = head; i > tale; i--) {
    for (j = 0; src_number >= powpow(10, i); j++) src_number -= powpow(10, i);
    splited_num[k++] = j;
  }
}

void sevseg_LED::input_inteder_ary() {
  for (int i = 0; i < DIGITS_NUM; i++)
    for (int j = 0; j < SEGMENT_NUM; j++)
      inteder_ary[i][j] = convert_NUMintoARY(splited_num[i])[j];
}

void sevseg_LED::output_sevseg() {
  output_array(inteder_ary);
}

void sevseg_LED::set_digit_point(int i) {
  if (i == point) digit_point = 1;
  else digit_opint = 0;
}

// -------------------------- Output 7 segment LED (other function) ------------

double powpow(int a, int b) {
  double dest = 1;
  if (b > 0) for (int i = 0; i < b; i++) dest *= (double)a;
  if (b < 0) for (int i = 0; i > b; i--) dest /= (double)a;
  return dest;
}

int* convert_NUMintoARY(int element) {
  static int sevseg_ary[NUM_PATTERN][SEGMENT_NUM] = {
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
  for (int i = 0; i < DIGITS_NUM; i++) digit[i] = 1;
}

void mbedLED_init() {
  for (int i = 0; i < MBED_LED_NUM; i++) mbed_LED[i] = 0;
}

void output_digit(int out_digit[SEGMENT_NUM]) {
  for (int i = 0; i < SEGMENT_NUM; i++) segment[i] = out_digit[i];
}

void output_array(int inteder_array[DIGITS_NUM][SEGMENT_NUM]) {
  for (int i = 0; i < DIGITS_NUM; i++) {
    digits_init();
    digit[i] = 0;
    output_digit(inteder_array[i]); 
    wait(powpow(10, -3));
  }
}
