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
>
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

### その他

## モード選択に関するもの

## 温度計に関するもの

## カウンターに関するもの

## エラーメッセージに関するもの
