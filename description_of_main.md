# main.cppの説明

## インクルードファイル

>今回は mbed用のインクルードファイルのみ  
>
>```C++
>#include "mbed.h"
>```

## オブジェクト形式マクロ  

>記号定数の定義をしています  
>これ以降の記述に対して、MBED_VOLTAGE→3.3  SEGMENT_NUM→7 のように  
>マクロ置換がなされます  
>
>```C++
>#define MBED_VOLTAGE 3.3
>#define ON 1
>#define OFF 0
>#define SEGMENT_NUM 7
>#define DIGITS_NUM 3
>#define NUM_PATTERN 10
>#define MBED_LED_NUM 4
>#define WAIT_NUM 5
>
>#define SEGMENT_A p10
>#define SEGMENT_B p11
>#define SEGMENT_C p12
>#define SEGMENT_D p13
>#define SEGMENT_E p14
>#define SEGMENT_F p15
>#define SEGMENT_G p16
>#define SEG_POINT p17
>
>#define SWITCH_R p18
>#define SWITCH_L p19
>
>#define TMP_SENSOR_PIN p20
>
>#define DIG_1_PIN p21
>#define DIG_2_PIN p22
>#define DIG_3_PIN p23
>```

## グローバル変数

>どの関数からでも参照できる変数です  
>7セグLEDのサンプルコードでa~gやdig1~dig3で宣言されていた変数は  
>DigitalOut型の配列として、まとめて扱っています  
>
>```C++
>DigitalOut segment[SEGMENT_NUM] = {
>  DigitalOut (SEGMENT_A),
>  DigitalOut (SEGMENT_B),
>  DigitalOut (SEGMENT_C),
>  DigitalOut (SEGMENT_D),
>  DigitalOut (SEGMENT_E),
>  DigitalOut (SEGMENT_F),
>  DigitalOut (SEGMENT_G)
>};
>
>DigitalOut digit[DIGITS_NUM] = {
>  DigitalOut (DIG_1_PIN),
>  DigitalOut (DIG_2_PIN),
>  DigitalOut (DIG_3_PIN)
>};
>
>DigitalOut mbed_LED[MBED_LED_NUM] = {
>  DigitalOut (LED1),
>  DigitalOut (LED2),
>  DigitalOut (LED3),
>  DigitalOut (LED4)
>};
>
>DigitalOut digit_point(SEG_POINT);
>```

## 関数プロトタイプ

>コンパイルエラー等を防ぐために、あらかじめ関数を定義しています  
>必ず記述しなければならないわけでもないので  
>そこまで気にする必要はないです  
>
>```C++
>int switch_reader(int ch);
>int mode_reader();
>void wait_switch_left();
>int starter_switch();
>int mode_switcher();
>int split_count(int count, int maximam);
>void Thermometer();
>double get_Temperature();
>double tmp_stopper();
>void Counter();
>int count_stopper(int current_push);
>int change_param(int counter);
>double powpow(int a, int b);
>int* convert_NUMintoARY(int element);
>void digits_init();
>void mbedLED_init();
>void output_digit(int out_digit[SEGMENT_NUM]);
>void output_array(int inteder_array[DIGITS_NUM][SEGMENT_NUM]);
>void disp_limit_sevseg(int lim);
>void disp_limit_LED(int lim);
>void Err_message();
>```

## main関数

>メイン関数です  
>プログラムはメイン関数を始めに実行し  
>メイン関数を軸に処理がなされます  
>
>```C++
>int main() {
>  while (1) {
>    digits_init();
>    mbedLED_init();
>    wait_switch_left();
>
>    switch (starter_switch()) {
>    case 1:
>      Thermometer();
>      break;
>    case 2:
>      Counter();
>      break;
>     default:
>      Err_message();
>    }
>  }
>}
>```

## スイッチ操作に関するもの

>```C++ int switch_reader(int ch); ```  
>引数(ch)でスイッチの左(1)or右(0)を指定して  
>指定されたスイッチが  
>押されていたら1, 押されていなかったら0を返す  
>
>```C++
>int switch_reader(int ch) {
>  DigitalIn tact_switch[2] = {
>    DigitalIn (SWITCH_R),
>    DigitalIn (SWITCH_L)
>  };
>  return tact_switch[ch];
>}
>```
************************************************************
>```C++ int mode_reader(); ```  
>左右のスイッチの値を受け取って  
>両方とも押されてない→ 0 0 → 0  
>右だけ押されている  → 0 1 → 1  
>左だけ押されている  → 1 0 → 2  
>両方とも押されている→ 1 1 → 3  
>の値を返し、以後これらをモードの値とする  
>
>```C++
>int mode_reader() {
>  if (switch_reader(0) == 0 && switch_reader(1) == 0) return 0;
>  if (switch_reader(0) == 0 && switch_reader(1) == 1) return 1;
>  if (switch_reader(0) == 1 && switch_reader(1) == 0) return 2;
>  if (switch_reader(0) == 1 && switch_reader(1) == 1) return 3;
>}
>```
************************************************************
>```C++ void wait_switch_left(); ```  
>モード選択時の誤作動を防ぐために  
>スイッチから一旦手を離してもらう  
>その後小休止を置いてモード選択に移る  
>
>```C++
>void wait_switch_left() {
>  while (mode_reader() != 0) ;
>  wait(0.1);
>}
>```

## モード選択に関するもの

>```C++ int starter_switch(); ```  
>モード選択に使う関数  
>スイッチが押されない限り7セグLEDのイルミネーションを表示し、  
>何か押されたらループを抜けてその時のモードの値を返す  
>
>```C++
>int starter_switch() {
>  while (1) {
>    for (int count = 0; count < powpow(10, 3); count++) {
>      disp_illumi_sevseg(split_count(count, powpow(10, 3)));
>      if (mode_reader() != 0) return mode_reader();
>    }
>  }
>}
>```
>***********************************************************
>```C++ int mode_switcher(); ```  
>モード切替に使う関数  
>スイッチが両方とも押されていたらcountを増やしていき  
>その値に対応してmbedのLEDを点灯させる  
>スイッチが離された時はcountを0に戻し、LEDを消灯させる  
>countが750未満なら1, 750以上なら0を返す  
>これをwhileの条件式内に記述することで  
>750未満→ループ続行、750以上→ループ脱出となる  
>
>```C++
>int mode_switcher() {
>  static int count;
>  if (mode_reader() != 3) {
>    count = 0;
>    mbedLED_init();
>  }
>  disp_illumi_LED(split_count(count, 750));
>  return (count++ < 750) ? 1 : 0;
>}
>```
>***********************************************************
>```C++ int split_count(int count, int maximam); ```  
>maximam(上限)を設定し、countがmaximamを5分割したうちどこに位置するのかを返す  
>例えば maximam = 500 と設定した時、  
> 0  ≦ count < 100 →　0  
>100 ≦ count < 200 →　1  
>200 ≦ count < 300 →　2  
>300 ≦ count < 400 →　3  
>400 ≦ count < 500 →　4  
>を返します  
>
>```C++
>int split_count(int count, int maximam) {
>  int unit = maximam / WAIT_NUM;
>  int i;
>  for (i = 1; (count - unit * i) > 0; i++) ;
>  return i - 1;
>}
>```
>***********************************************************
>```C++ void disp_illumi_sevseg(int lim); ```  
>モード選択時の7セグLEDイルミネーションを表示する関数  
>独自の二次元配列を用意し、また0~4の引数を受け取って  
>3桁同時に5パターンの表示を行います  
>どのパターンを表示するかは引数により決めらます  
>
>```C++
>void disp_illumi_sevseg(int lim) {
>  int wait_array[WAIT_NUM][SEGMENT_NUM] = {
>    {OFF, OFF, OFF, ON,  OFF, OFF, OFF},
>    {OFF, OFF, ON,  OFF, ON,  OFF, OFF},
>    {OFF, OFF, OFF, OFF, OFF, OFF, ON },
>    {OFF, ON,  OFF, OFF, OFF, ON,  OFF},
>    {ON,  OFF, OFF, OFF, OFF, OFF, OFF}
>  };
>  for (int i = 0; i < DIGITS_NUM; i++) {
>    digits_init();
>    digit[i] = 0;
>    output_digit(wait_array[lim]);
>    wait(0.001);
>  }
>}
>```
>***********************************************************
>```C++ void disp_illumi_LED(int lim); ```  
>モード変更時のmbed_LEDのイルミネーションを表示する関数  
>引数(0~4)によって何個目まで点灯させるかが決定されます  
>
>```C++
>void disp_illumi_LED(int lim) {
>  for (int i = 0; i < lim; i++) mbed_LED[i] = 1; 
>}
>```

## 温度計に関するもの

>```C++ void Thermometer(); ```  
>温度計に必要な処理を1セットにまとめたもの  
>
>```C++
>void Thermometer() {
>  double tmp_data;
>  sevseg_LED tmp(1);
>
>  while (mode_switcher()) {
>    tmp_data = tmp_stopper();
>    tmp.set_number(tmp_data);
>    tmp.split_Numerical_Pos();
>    tmp.input_inteder_ary();
>    tmp.output_sevseg();
>  }
>}
>```
>***********************************************************
>```C++ double get_Temperature(); ```  
>温度データ読み取り専用の関数  
>AnalogInから電圧を読み取ったあと  
>温度データを計算&導出  
>
>```C++
>double get_Temperature() {
>  AnalogIn tmp_sensor(TMP_SENSOR_PIN);
>  double changed_vol = tmp_sensor * MBED_VOLTAGE;
>  return changed_vol * 100;
>}
>```
>**********************************************************
>```C++ double tmp_stopper(); ```  
>一定の間隔を置いて温度データを更新するための関数  
>stock(温度データ保存用)とcounterを用意して、  
>関数をコールするたびにcountを増やしcountが500を超えたら0に戻す  
>count = 0 ならstockを更新する  
>
>```C++
>double tmp_stopper() {
>  static double stock;
>  static int count;
>  if (count++ > 500) count = 0;
>  if (!count) stock = get_Temperature();
>  return stock;
>}
>```

## カウンターに関するもの

>```C++ void Counter(); ```  
>カウンターに必要な処理を一式にまとめたもの  
>
>```C++
>void Counter() {
>  static int param;
>  sevseg_LED Counter(2);
>
>  while (mode_switcher()) {
>    param = change_param(param);
>    Counter.set_number(param);
>    Counter.split_Numerical_Pos();
>    Counter.input_inteder_ary();
>    Counter.output_sevseg();
>  }
>}
>```
>***********************************************************
>```C++ int count_stopper(int current_push); ```  
>スイッチの状態が変化した瞬間のみモードの値を返す  
>change_param内のswitch文に導入することで  
>長押しによるparamの操作が無効となる  
>
>```C++
>int count_stopper(int current_push) {
>  static int previous_push;
>  int judge = previous_push - current_push;
>  previous_push = current_push;
>  if (!judge) return 0;
>  else return current_push;
>}
>```
>***********************************************************
>```C++ int change_param(int counter); ```  
>Counter関数のparamの値を操作する  
>
>```C++
>int change_param(int counter) {
>  switch (count_stopper(mode_reader())) {
>  case 1:
>    counter++;
>    break;
>  case 2:
>    if (counter > 0)
>      counter--;
>    break;
>  case 3:
>    counter = 0;
>    break;
>  }
>  return counter;
>}
>```

## 7セグメントLEDに関するもの

### sevseg_LEDクラス

>数値入力から出力までに必要なデータや、それらを操作する関数を
>一式にまとめているようなものです
>モードをそれぞれ実行する際に宣言されています
>
>```C++
>class sevseg_LED {
>  int head, tale;   // 数値の先頭の桁、最後の桁をクラス宣言時に設定します
>  int point;   //　
>  double src_number;   //
>  int splited_num[DIGITS_NUM];   //
>  int inteder_ary[DIGITS_NUM][SEGMENT_NUM];   //
>public:
>  sevseg_LED(int head);
>  void set_number(double input_num);
>  void split_Numerical_Pos();
>  void input_inteder_ary();
>  void output_console();
>  void output_sevseg();
>  void set_digit_point(int i);
>};
>```

### class sevseg_LEDのメンバ関数

>
>```C++ sevseg_LED::sevseg_LED(int input_head); ```  
>クラスsevseg_LEDのコンストラクタ  
>sevseg_LED型の変数を定義する際に以下の処理がなされます  
>引数に先頭の位を入れてheadを設定、それに応じてpoint, taleも定めます  
>
>```C++
>sevseg_LED::sevseg_LED(int input_head) {
>  head = input_head;
>  point = head;
>  tale = head - DIGITS_NUM;
>}
>```
>***********************************************************
>```C++ void sevseg_LED::set_number(double input_num); ```  
>表示する数値を設定するだけの関数  
>
>```C++
>void sevseg_LED::set_number(double input_num) {
>  src_number = input_num;
>}
>```
>***********************************************************
>```C++ void sevseg_LED::split_Numerical_Pos(); ```  
>表示する数値(src_number)を桁ごとに分割する関数  
>桁ごとの数字はint型の配列(splited_num[])に格納されます  
>
>```C++
>void sevseg_LED::split_Numerical_Pos() {
>  int i, j, k = 0;
>  for (i = head; i > tale; i--) {
>    for (j = 0; src_number >= powpow(10, i); j++) src_number -= powpow(10, i);
>    splited_num[k++] = j;
>  }
>}
>```
>***********************************************************
>```C++ void sevseg_LED::input_inteder_ary(); ```  
>桁ごとの数字に対応するON/OFFの並びをconvert_NUMintoARYから参照して  
>二次元配列(inteder_ary[][])に格納します  
>
>```C++
>void sevseg_LED::input_inteder_ary() {
>  for (int i = 0; i < DIGITS_NUM; i++)
>    for (int j = 0; j < SEGMENT_NUM; j++)
>      inteder_ary[i][j] = convert_NUMintoARY(splited_num[i])[j];
>}
>```
>***********************************************************
>```C++ void sevseg_LED::output_sevseg(); ```  
>以上の処理が完了した二次元配列(inteder_ary)を  
>output_array(配列表示関数)に代入するだけの関数  
>
>```C++
>void sevseg_LED::output_sevseg() {
>  output_array(inteder_ary);
>}
>```
>***********************************************************
>```C++ void sevseg_LED::set_digit_point(int i); ```  
>小数点の操作をする関数です  
>output_array内で一の位を表示をしている時に小数点を点灯させます  
>
>```C++
>void sevseg_LED::set_digit_point(int i) {
>if (i == point) digit_point = 1;
>  else digit_point = 0;
>}
>```

### その他の関数

>```C++ double powpow(int a, int b); ```  
>aのb乗を返す関数  
>split_Numerical_Pos内ではbの部分を1ずつ小さくすることで  
> 10 → 1 → 0.1 のように変化させています  
>
>```C++
>double powpow(int a, int b) {
>  double dest = 1;
>  if (b > 0) for (int i = 0; i < b; i++) dest *= (double)a;
>  if (b < 0) for (int i = 0; i > b; i--) dest /= (double)a;
>  return dest;
>}
>```
>***********************************************************
>```C++ int* convert_NUMintoARY(int element); ```  
>引数に0~9の数字を入れると、それぞれに対応するON/OFFの配列(の先頭アドレス)を返します  
>0~9以外の数字が入った場合はErr(エラー)を表示  
>引数に5を入れた場合、  
>convert_NUMintoARY(5)[0] == ON   
>convert_NUMintoARY(5)[1] == OFF  
>convert_NUMintoARY(5)[2] == ON  
>convert_NUMintoARY(5)[3] == ON  
>convert_NUMintoARY(5)[4] == OFF  
>convert_NUMintoARY(5)[5] == ON  
>convert_NUMintoARY(5)[6] == ON  
>のようになります  
>
>```C++
>int* convert_NUMintoARY(int element) {
>  int sevseg_ary[NUM_PATTERN][SEGMENT_NUM] = {
>    {ON,  ON,  ON,  ON,  ON,  ON , OFF}, // for 0
>    {OFF, ON,  ON,  OFF, OFF, OFF, OFF}, // for 1
>    {ON,  ON,  OFF, ON,  ON,  OFF, ON }, // for 2
>    {ON,  ON,  ON,  ON,  OFF, OFF, ON }, // for 3
>    {OFF, ON , ON,  OFF, OFF, ON,  ON }, // for 4
>    {ON,  OFF, ON,  ON,  OFF, ON , ON }, // for 5
>    {ON,  OFF, ON,  ON,  ON,  ON,  ON }, // for 6
>    {ON,  ON,  ON,  OFF, OFF, OFF, OFF}, // for 7
>    {ON,  ON,  ON,  ON,  ON,  ON,  ON }, // for 8
>    {ON,  ON,  ON,  ON,  OFF, ON,  ON }  // for 9
>  };
>  if (element < 0 || 9 < element) Err_message();
>  return sevseg_ary[element];
>}
>```
>***********************************************************
>```C++ void digits_init(); ```  
>7セグLEDを初期化する関数  
>すべての桁のdigitに1を代入し、消灯させます  
>
>```C++
>void digits_init() {
>  for (int i = 0; i < DIGITS_NUM; i++) digit[i] = 1;
>}
>```
>***********************************************************
>```C++ void mbedLED_init(); ```  
>mbedに付いているLEDをすべて消灯し初期化する関数  
>
>```C++
>void mbedLED_init() {
>  for (int i = 0; i < MBED_LED_NUM; i++) mbed_LED[i] = 0;
>}
>```
>***********************************************************
>```C++ void output_digit(int out_digit[SEGMENT_NUM]); ```  
>桁ひとつぶんを表示する関数  
>1桁ぶんのON/OFFの配列を受け取って、a~gに順番に代入します  
>
>```C++
>void output_digit(int out_digit[SEGMENT_NUM]) {
>  for (int i = 0; i < SEGMENT_NUM; i++) segment[i] = out_digit[i];
>}
>```
>***********************************************************
>```C++ void output_array(int inteder_array[DIGITS_NUM][SEGMENT_NUM]); ```  
>ON/OFFの並びを7セグLEDに出力する関数  
>二次元配列を受け取って表示する桁を切り替えながら  
>output_digit, set_digit_pointをコールします  
>
>```C++
>void output_array(int inteder_array[DIGITS_NUM][SEGMENT_NUM]) {
>  for (int i = 0; i < DIGITS_NUM; i++) {
>    digits_init();
>    digit[i] = 0;
>    output_digit(inteder_array[i]); 
>    set_digit_point(i);
>    wait(powpow(0.001));
>  }
>}
>```

## エラーメッセージに関するもの

>```C++ void Err_message(); ```  
>独自の二次元配列を用意してErr(エラー)を表示します  
>
>```C++
>void Err_message() {
>  int error_array[DIGITS_NUM][SEGMENT_NUM] = {
>    {ON,  OFF, OFF, ON,  ON, ON,  ON},
>    {OFF, OFF, OFF, OFF, ON, OFF, ON},
>    {OFF, OFF, OFF, OFF, ON, OFF, ON}
>  };
>  while (mode_switcher()) output_array(error_array);
>}
>```