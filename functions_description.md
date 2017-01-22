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
>    
>    wait_switch_left();
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

>**int switch_reader(int ch);**    
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

>**int mode_reader();**  
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

>**void wait_switch_left();**  
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

>**int starter_switch();**  
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
>
>**int mode_switcher();**  
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

>**int split_count(int count, int maximam);**  
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

## 温度計に関するもの

## カウンターに関するもの

## エラーメッセージに関するもの
