#include "mbed.h"

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

enum Mode {
  INIT,
  MODE_SELECT,
  MODE_SWITCHER,
  THERMOMETER,
  COUNTER
};

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

DigitalOut mbed_LED[MBED_LED_NUM] = {
  DigitalOut (LED1),
  DigitalOut (LED2),
  DigitalOut (LED3),
  DigitalOut (LED4)
};

DigitalOut digit_point(SEG_POINT);

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
  int show_digit_point();
  void output_sevseg(int pos);
};

bool is_pushed(int ch);
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
void disp_illumi_sevseg(int lim);
void disp_illumi_LED(int lim);
void Err_message();
void output_array(int inteder_array[DIGITS_NUM][SEGMENT_NUM]);
void output_array(int inteder_array[DIGITS_NUM][SEGMENT_NUM], int pos);

int main() {
  
  sevseg_LED tmp(1), count(2);
  Mode mode;
  
  while (1) {
    switch (mode){
    case INIT:
      mode = task_init();
      break;
    case MODE_SELECT:
      mode = task_select;
      break;
    case MODE_SWITCHER:
      mode = task_switcher();
    case THERMOMETER:
      mode = task_thermo();
      break;
    case COUNTER:
      mode = task_count();
      break;
    }
    
    // digits_init();
    // mbedLED_init();
    // wait_switch_left();

    // switch (starter_switch()) {
    // case 1:
    //   Thermometer();
    //   break;
    // case 2:
    //   Counter();
    //   break;
    // default:
    //   Err_message();
    // }
  }
}

bool is_pushed(int ch) {
  static DigitalIn tact_switch[2] = {
    DigitalIn (SWITCH_R),
    DigitalIn (SWITCH_L)
  };
  return tact_switch[ch];
}

int mode_reader() {
  int left_switch = is_pushed(0), int right_switch = is_pushed(1);
  return (left_switch << 1) | right_switch;
}

void wait_switch_left() {
  while (mode_reader() != 0) ;
  wait(0.1);
}

int starter_switch() {
  while (1) {
    for (int count = 0; count < powpow(10, 3); count++) {
      disp_illumi_sevseg(split_count(count, powpow(10, 3)));
      if (mode_reader() != 0) return mode_reader();
    }
  }
}

int mode_switcher() {
  static int count;
  if (mode_reader() != 3) {
    count = 0;
    mbedLED_init();
  }
  disp_illumi_LED(split_count(count, 750));
  return (count++ < 750) ? 1 : 0;
}

int split_count(int count, int maximam) {
  int unit = maximam / WAIT_NUM;
  int i;
  for (i = 1; (count - unit * i) > 0; i++) ;
  return i - 1;
}

void disp_illumi_sevseg(int lim) {
  int wait_array[WAIT_NUM][SEGMENT_NUM] = {
    {OFF, OFF, OFF, ON,  OFF, OFF, OFF},
    {OFF, OFF, ON,  OFF, ON,  OFF, OFF},
    {OFF, OFF, OFF, OFF, OFF, OFF, ON },
    {OFF, ON,  OFF, OFF, OFF, ON,  OFF},
    {ON,  OFF, OFF, OFF, OFF, OFF, OFF}
  };
  for (int i = 0; i < DIGITS_NUM; i++) {
    digits_init();
    digit[i] = 0;
    output_digit(wait_array[lim]);
    wait(0.001);
  }
}

void disp_illumi_LED(int lim) {
  for (int i = 0; i < lim; i++) mbed_LED[i] = 1; 
}

void Thermometer() {
  double tmp_data;
  sevseg_LED tmp(1);

  while (mode_switcher()) {
    tmp_data = tmp_stopper();
    tmp.set_number(tmp_data);
    tmp.split_Numerical_Pos();
    tmp.input_inteder_ary();
    tmp.output_sevseg(tmp.show_digit_point());
  }
}

double get_Temperature() {
  AnalogIn tmp_sensor(TMP_SENSOR_PIN);
  double changed_vol = tmp_sensor * MBED_VOLTAGE;
  return changed_vol * 100;
}

double tmp_stopper() { // meke shorter!
  static double stock;
  static int count;
  if (count > 500) count = 0;
  if (!count++) stock = get_Temperature();
  return stock;
}

void Counter() {
  static int param;
  sevseg_LED Counter(2);

  while (mode_switcher()) {
    param = change_param(param);
    Counter.set_number(param);
    Counter.split_Numerical_Pos();
    Counter.input_inteder_ary();
    Counter.output_sevseg(Counter.show_digit_point());
  }
}

int count_stopper(int current_push) {
  static int previous_push;
  int judge = previous_push - current_push;
  previous_push = current_push;
  if (!judge) return 0;
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

int sevseg_LED::show_digit_point() {
  return point;
}

void sevseg_LED::output_sevseg(int pos) {
  output_array(inteder_ary, pos);
}

double powpow(int a, int b) {
  double dest = 1;
  if (b > 0) for (int i = 0; i < b; i++) dest *= (double)a;
  if (b < 0) for (int i = 0; i > b; i--) dest /= (double)a;
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
  digit_point = 0;
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
    wait(0.001);
  }
}

void output_array(int inteder_array[DIGITS_NUM][SEGMENT_NUM], int pos) {
  for (int i = 0; i < DIGITS_NUM; i++) {
    digits_init();
    digit[i] = 0;
    output_digit(inteder_array[i]);
    if (pos == i) digit_point = 1;
    else digit_point = 0;
    wait(0.001);
  }
}

void Err_message() {
  int error_array[DIGITS_NUM][SEGMENT_NUM] = {
    {ON,  OFF, OFF, ON,  ON, ON,  ON},
    {OFF, OFF, OFF, OFF, ON, OFF, ON},
    {OFF, OFF, OFF, OFF, ON, OFF, ON}
  };
  while (mode_switcher()) output_array(error_array);
}
