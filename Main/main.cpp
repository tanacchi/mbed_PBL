// ------------------------- Include files -------------------------------------
#include "mbed.h"

// ------------------------- Definition ----------------------------------------
#define MBED_VOLTAGE 3.3

#define ON 1
#define OFF 0
#define SEGMENT_NUM 7
#define DIGITS_NUM 3
#define NUM_PATTERN 10

#define TMP_SENSOR_PIN p20

#define SEGMENT_A p10
#define SEGMENT_B p11
#define SEGMENT_C p12
#define SEGMENT_D p13
#define SEGMENT_E p14
#define SEGMENT_F p15
#define SEGMENT_G p16
#define SEGMENT_POINT p17

#define DIG_1_PIN p21
#define DIG_2_PIN p22
#define DIG_3_PIN p23

#define WIDTH 3

#define SWITCH_R p18
#define SWITCH_L p19

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

// ------------------------- 7 segment LED class -------------------------------
class sevseg_LED {
  int head, tale;
  double src_number;
  int splited_num[WIDTH];
  int output_array[WIDTH][SEGMENT_NUM];
public:
  sevseg_LED(int head);
  void set_number(double input_num);
  void split_Numerical_Pos();
  void input_inteder_ary();
  void output_console();
  void output_sevseg();
};

// ------------------------- Function prototype --------------------------------
double powpow(int a, int b);
double get_Temperature();
void digits_init();
int* convert_NUMintoARY(int element);
void output_digit(int out_digit[SEGMENT_NUM]);
void Thermometer();
void Counter();
int minute_counter();
double average_Temperature();
double tmp_stopper();
int mode_reader();
int switch_reader(int ch);
int starter_switch();
void err_message();
void wait_switch_left();
int mode_switcher();

// ========================== Test space =======================================
int count_stopper(int current_push) {
  static int previous_push;
  int judge = previous_push - current_push;
  previous_push = current_push;
  if (judge == 0) return 0;
  else return current_push;
}

int change_param(int counter) {
  switch (count_stopper(mode_reader())) {
  case 1:
    counter++;
    break;
  case 2:
    if (counter > 0)
      counter--;
    break;
  case 3:
    counter = 0;
    break;
  }
  return counter;
}
void Counter() {
  sevseg_LED Counter(2);
  static int param;
  while (mode_switcher()) {
    param = change_param(param);
    Counter.set_number(param);
    Counter.split_Numerical_Pos();
    Counter.input_inteder_ary();
    Counter.output_sevseg();
  }
}

// =============================================================================

// ------------------------- Main function -------------------------------------
int main()
{
  while (1) {
    wait_switch_left();
    switch(starter_switch()) {
    case 0:
      Thermometer();
      break;
    case 1:
      Counter();
      break;
    case 2:
      sevseg_LED sw(2);
      while (mode_switcher()) {
        sw.set_number(mode_reader());
        sw.split_Numerical_Pos();
        sw.input_inteder_ary();
        sw.output_sevseg();
      }
      break;
    default:
      err_message();
    }
  }
}

// ------------------------- About switch --------------------------------------
int switch_reader(int ch) {
  DigitalIn tact_switch[2] = {
    DigitalIn (SWITCH_R),
    DigitalIn (SWITCH_L)
  };
  return tact_switch[ch];
}

int mode_reader() {
  if (switch_reader(0) == 0 && switch_reader(1) == 0) return 0;
  if (switch_reader(0) == 0 && switch_reader(1) == 1) return 1;
  if (switch_reader(0) == 1 && switch_reader(1) == 0) return 2;
  if (switch_reader(0) == 1 && switch_reader(1) == 1) return 3;
}

void wait_switch_left() {
  digits_init();
  while (mode_reader() != 0) ;
  wait(powpow(10, -1) * 5);
}

// ------------------------- Mode select ---------------------------------------
int starter_switch() {
  for (int i = 0; i < powpow(10, 5); i++)
    if (mode_reader() != 0) return mode_reader(); // <-- 0

  return 0;
}

int mode_switcher() {
  static unsigned int count;

  if (mode_reader() == 3) count++;
  else count = 0;

  return (count < powpow(10, 3)) ? 1 : 0;
}

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

double get_Temperature() {
  AnalogIn tmp_sensor(TMP_SENSOR_PIN);
  double replyed_vol = tmp_sensor * MBED_VOLTAGE;
  return replyed_vol * 100;
}

double tmp_stopper() { // meke shorter!
  static double stock = 0;
  static int counter;
  if (counter > 5 * powpow(10, 2)) counter = 0;
  if (++counter == 1) stock = get_Temperature();

  return stock;
}

// -------------------------- Counter ---------------------------------------

// ------------------------- Output 7 segment LED (member function) ------------
sevseg_LED::sevseg_LED(int input_head) {
  head = input_head;
  tale = head - WIDTH;
  for (int i = 0; i < WIDTH; i++)
    splited_num[i] = 0;
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
  for (int i = 0; i < WIDTH; i++)
    for (int j = 0; j < SEGMENT_NUM; j++)
      output_array[i][j] = convert_NUMintoARY(splited_num[i])[j];
}

void sevseg_LED::output_sevseg() {
  for (int i = 0; i < WIDTH; i++) {
    digits_init();
    digit[i] = 0;
    output_digit(output_array[i]);
    wait(powpow(10, -3));
  }
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
  if (element < 0 || 9 < element) err_message();
  return sevseg_ary[element];
}

void digits_init() {
  for (int i = 0; i < WIDTH; i++) digit[i] = 1;
}

void output_digit(int out_digit[SEGMENT_NUM]) {
  for (int i = 0; i < SEGMENT_NUM; i++)
    segment[i] = out_digit[i];
}

// ------------------------- ERROR message -------------------------------------
void err_message() {
  int error_array[3][7] = {
    {ON,  OFF, OFF, ON,  ON, ON,  ON},
    {OFF, OFF, OFF, OFF, ON, OFF, ON},
    {OFF, OFF, OFF, OFF, ON, OFF, ON}
  };
  while (1) {
    for (int i = 0; i < WIDTH; i++) {
      digits_init();
      digit[i] = 0;
      output_digit(error_array[i]);
      wait(powpow(10, -3));
    }
  }
}
