# main.cppの説明

## インクルードファイル

>今回は mbed用のインクルードファイルのみです  
>
>```C++
> #include "mbed.h"
>```

## オブジェクト形式マクロ  

>記号定数の定義をしています  
>これ以降の記述に対して、MBED_VOLTAGE→3.3  SEGMENT_NUM→7 のように  
>置換がなされます  
>
>```C++
> #define MBED_VOLTAGE 3.3
> #define ON 1
> #define OFF 0
> #define SEGMENT_NUM 7
> #define DIGITS_NUM 3
> #define NUM_PATTERN 10
> #define MBED_LED_NUM 4
> #define WAIT_NUM 5
>
> #define SEGMENT_A p10
> #define SEGMENT_B p11
> #define SEGMENT_C p12
> #define SEGMENT_D p13
> #define SEGMENT_E p14
> #define SEGMENT_F p15
> #define SEGMENT_G p16
> #define SEG_POINT p17
>
> #define SWITCH_R p18
> #define SWITCH_L p19
> 
> #define TMP_SENSOR_PIN p20
> 
> #define DIG_1_PIN p21
> #define DIG_2_PIN p22
> #define DIG_3_PIN p23
>```

## グローバル変数

>どの関数からでも参照できる変数です  
>7セグLEDのサンプルコードでa~gやdig1~dig3で宣言されていた変数は  
>DigitalOut型の配列として、まとめて扱っています  
>
>```C++
> DigitalOut segment[SEGMENT_NUM] = {
>   DigitalOut (SEGMENT_A),
>   DigitalOut (SEGMENT_B),
>   DigitalOut (SEGMENT_C),
>   DigitalOut (SEGMENT_D),
>   DigitalOut (SEGMENT_E),
>   DigitalOut (SEGMENT_F),
>   DigitalOut (SEGMENT_G)
> };
>
> DigitalOut digit[DIGITS_NUM] = {
>   DigitalOut (DIG_1_PIN),
>   DigitalOut (DIG_2_PIN),
>   DigitalOut (DIG_3_PIN)
> };
>
> DigitalOut mbed_LED[MBED_LED_NUM] = {
>   DigitalOut (LED1),
>   DigitalOut (LED2),
>   DigitalOut (LED3),
>   DigitalOut (LED4)
> };
>
> DigitalOut digit_point(SEG_POINT);
>```

## 関数プロトタイプ

>コンパイルエラー等を防ぐために、あらかじめ関数を定義しています  
>必ず記述しなければならないわけでもないので  
>そこまで気にする必要はないです  
>
>```C++
> int switch_reader(int ch);
> int mode_reader();
> void wait_switch_left();
> int starter_switch();
> int mode_switcher();
> int split_count(int count, int maximam);
> void Thermometer();
> double get_Temperature();
> double tmp_stopper();
> void Counter();
> int count_stopper(int current_push);
> int change_param(int counter);
> double powpow(int a, int b);
> int* convert_NUMintoARY(int element);
> void digits_init();
> void mbedLED_init();
> void output_digit(int out_digit[SEGMENT_NUM]);
> void output_array(int inteder_array[DIGITS_NUM][SEGMENT_NUM]);
> void disp_limit_sevseg(int lim);
> void disp_limit_LED(int lim);
> void Err_message();
>```

## main関数

>メイン関数です  
>メイン関数が始めに実行されます  
>
>```C++
> int main() {
>   while (1) {             // whileの内を無限ループ
>     digits_init();        // 7セグLEDを初期化
>     mbedLED_init();       // mbed_LEDを初期化
>     wait_switch_left();   // スイッチが離されるまで待つ
>
>     switch (starter_switch()) {  // モードを取得
>     case 1:               // モード1なら
>       Thermometer();        // 温度計
>       break;
>     case 2:               // モード2なら
>       Counter();           // カウンター
>       break;
>     default:           // それ以外なら
>       Err_message();     // エラーを表示
>     }
>   }
> }
>```

## スイッチ操作に関するもの

>```C++ 
> int switch_reader(int ch); 
>```
>
>引数(ch)でスイッチの左(1)or右(0)を指定して  
>指定されたスイッチが  
>押されていたら1, 押されていなかったら0を返します  
>
>```C++
> int switch_reader(int ch) {
>   DigitalIn tact_switch[2] = {
>     DigitalIn (SWITCH_R),     // tact_switch[0] → 右のスイッチの値
>     DigitalIn (SWITCH_L)      // tact_switch[1] → 左のスイッチの値
>   };
>   return tact_switch[ch];     // 引数で指定されたスイッチの値を返す
> }
>```
************************************************************
>```C++ 
> int mode_reader(); 
>```  
>左右のスイッチの値を受け取って  
>両方とも押されてない→ 0 0 → 0  
>右だけ押されている  → 0 1 → 1  
>左だけ押されている  → 1 0 → 2  
>両方とも押されている→ 1 1 → 3  
>の値を返し、以後これらをモードの値とします  
>
>```C++
> int mode_reader() {
>   if (switch_reader(0) == 0 && switch_reader(1) == 0) return 0;  // 0 0 → 0を返す
>   if (switch_reader(0) == 0 && switch_reader(1) == 1) return 1;  // 0 1 → 1を返す
>   if (switch_reader(0) == 1 && switch_reader(1) == 0) return 2;  // 1 0 → 2を返す
>   if (switch_reader(0) == 1 && switch_reader(1) == 1) return 3;  // 1 1 → 3を返す
> }
>```
************************************************************
>```C++ 
> void wait_switch_left(); 
>```  
>モード選択時の誤作動を防ぐために  
>スイッチから一旦手を離してもらいます  
>その後小休止を置いてモード選択に移ります  
>
>```C++
> void wait_switch_left() {
>   while (mode_reader() != 0) ;   // スイッチがフリーになるまで何もしない( ";" は何もしないの意味)
>   wait(0.1);                // 一瞬待つ
> }
>```

## モード選択に関するもの

>```C++ 
>int starter_switch(); 
>```  
>モード選択に使う関数です  
>スイッチが押されない間7セグLEDのイルミネーションを表示し、  
>何か押されたらループを抜けてその時のモードの値を返します  
>
>```C++
> int starter_switch() {
>   while (1) {
>     for (int count = 0; count < powpow(10, 3); count++) {    // countが1000になるまで繰り返す
>       disp_illumi_sevseg(split_count(count, powpow(10, 3)));    // countの値によってディスプレイのパターンを変える
>       if (mode_reader() != 0) return mode_reader();        // mode_readerから0以外の値が返ってきたらループを抜けてモードの値を返す
>     }
>   }
> }
>```
>***********************************************************
>```C++ 
> int mode_switcher(); 
>```  
>モード切替に使う関数です  
>スイッチが両方とも押されていたらcountを増やしていき  
>その値に対応してmbedのLEDを点灯させます  
>スイッチが離された時はcountを0に戻し、LEDを消灯させます  
>countが750未満なら1, 750以上なら0を返します  
>これをwhileの条件式内に記述することで  
>750未満→ループ続行、750以上→ループ脱出となります  
>
>```C++
> int mode_switcher() {
>   static int count;           // カウント用の変数を定義(値は保持される)
>   if (mode_reader() != 3) {　   // 両方押されていないなら
>     count = 0;                 // countを0に戻して
>     mbedLED_init();            // mbed_LEDを初期化
>   }
>   disp_illumi_LED(split_count(count, 750));  // countの値によってmbed_LEDを点灯させる
>   return (count++ < 750) ? 1 : 0;          // countを1ずつ増やしていき、
> }　　　　　　　　　　　　　　　　        　// 750未満なら1、750以上なら0
>```
>***********************************************************
>```C++ 
> int split_count(int count, int maximam); 
>```  
>maximam(上限)を設定し、countがmaximamを5分割したうちどこに位置するのかを返す関数です  
>例えば maximam = 500 と設定した時、  
> 0  ≦ count < 100 →　0  
>100 ≦ count < 200 →　1  
>200 ≦ count < 300 →　2  
>300 ≦ count < 400 →　3  
>400 ≦ count < 500 →　4  
>を返します  
>
>```C++
> int split_count(int count, int maximam) {
>   int unit = maximam / WAIT_NUM;        // maximamを5で割った値を1単位(unit)とする
>   int i;
>   for (i = 1; (count - unit * i) > 0; i++) ;   // countにunitが何個分入るか判断
>   return i - 1;                              // 何個分入るかを返す
> }
>```
>***********************************************************
>```C++ 
> void disp_illumi_sevseg(int lim); 
>```  
>モード選択時の7セグLEDイルミネーションを表示する関数です  
>独自の二次元配列を用意し、また0~4の引数を受け取って  
>3桁同時に5パターンの表示を行います  
>どのパターンを表示するかは引数により決めらます  
>
>```C++
> void disp_illumi_sevseg(int lim) {
>   int wait_array[WAIT_NUM][SEGMENT_NUM] = {   // イルミネーション用の配列
>     {OFF, OFF, OFF, ON,  OFF, OFF, OFF},      // 5パターン×7セグメント
>     {OFF, OFF, ON,  OFF, ON,  OFF, OFF},
>     {OFF, OFF, OFF, OFF, OFF, OFF, ON },
>     {OFF, ON,  OFF, OFF, OFF, ON,  OFF},
>     {ON,  OFF, OFF, OFF, OFF, OFF, OFF}
>   };
>   for (int i = 0; i < DIGITS_NUM; i++) {      // 3桁分繰り返す 
>     digits_init();                            // 7セグLEDを初期化
>     digit[i] = 0;                         // 表示する桁の指定(カソード側の電圧をLOWにする)
>     output_digit(wait_array[lim]);          // 1桁分表示
>     wait(0.001);  // 一瞬待つ
>   }
> }
>```
>***********************************************************
>```C++ 
> void disp_illumi_LED(int lim); 
>```  
>モード変更時のmbed_LEDのイルミネーションを表示する関数です  
>引数(0~4)によって何個目まで点灯させるかが決定されます  
>
>```C++
> void disp_illumi_LED(int lim) {
>   for (int i = 0; i < lim; i++) mbed_LED[i] = 1;  // lim番目までmbed_LEDを点灯
> }
>```

## 温度計に関するもの

>```C++ 
> void Thermometer(); 
>```  
>温度計に必要な処理を1セットにまとめたものです  
>
>```C++
> void Thermometer() {
>   double tmp_data;          // 温度データ格納用の変数
>   sevseg_LED tmp(1);        // 数値表示用のsevseg_LED型変数
> 
>   while (mode_switcher()) {    // mode_switcherから返ってくる値が0ならループ脱出
>     tmp_data = tmp_stopper();    // 温度データを取得・代入
>     tmp.set_number(tmp_data);    // 表示する数値を設定
>     tmp.split_Numerical_Pos();   // 桁ごとに分割
>     tmp.input_inteder_ary();     // 数字ごとの配列を参照・代入
>     tmp.output_sevseg();         // 7セグLEDに表示
>   }
> }
>```
>***********************************************************
>```C++ 
> double get_Temperature(); 
>```  
>温度データ読み取り専用の関数です  
>AnalogInから電圧を読み取ったあと  
>温度データを計算&導出します  
>
>```C++
> double get_Temperature() {
>   AnalogIn tmp_sensor(TMP_SENSOR_PIN);     // AnalogIn型変数を定義
>   double changed_vol = tmp_sensor * MBED_VOLTAGE;
>   return changed_vol * 100;               // 温度を計算して返す
> }
>```
>**********************************************************
>```C++ 
> double tmp_stopper(); 
>```  
>一定の間隔を置いて温度データを更新するための関数です  
>stock(温度データ保存用)とcounterを用意して、  
>関数をコールするたびにcountを増やしcountが500を超えたら0に戻します  
>count = 0 ならstockを更新します  
>
>```C++
> double tmp_stopper() {
>   static double stock;      // 温度データ格納用の変数
>   static int count;         // カウント用の変数
>   if (count++ > 500) count = 0;          // countを1つ増やし、500より大きければ0に戻す
>   if (!count) stock = get_Temperature();  // countが0なら温度データを更新
>   return stock;                          // 温度データを返す
> }
>```

## カウンターに関するもの

>```C++ 
> void Counter(); 
>```  
>カウンターに必要な処理を一式にまとめたものです  
>```C++
> void Counter() {
>   static int param;          // 操作するパラメータ
>   sevseg_LED Counter(2);     // 数値表示用のsevseg_LED型変数
> 
>   while (mode_switcher()) {         // mode_switcherから返ってくる値が0ならループ脱出
>     param = change_param(param);    // パラメータを操作する
>     Counter.set_number(param);      // 表示する数値を設定
>     Counter.split_Numerical_Pos();    // 桁ごとに分割
>     Counter.input_inteder_ary();     // 数字ごとの配列を参照・代入
>     Counter.output_sevseg();       // 7セグLEDに表示
>   }
> }
>```
>***********************************************************
>```C++ 
> int count_stopper(int current_push); 
>```  
>スイッチの状態が変化した瞬間のみモードの値を返します  
>change_param内のswitch文に導入することで  
>長押しによるparamの操作が無効となります  
>
>```C++
> int count_stopper(int current_push) {       // 引数として現在のスイッチの値を取得
>   static int previous_push;                 // 直前のスイッチの値を格納するための変数
>   int judge = previous_push - current_push;    // 直前のスイッチの値と現在のスイッチの値を比較
>   previous_push = current_push;              // 直前のスイッチの値を現在のものに更新
>   if (!judge) return 0;                    // 値の差が0 = スイッチに変化がなかった場合は0を返す
>   else return current_push;                 // 現在のスイッチの値を返す
> }
>```
>***********************************************************
>```C++ 
> int change_param(int counter); 
>```  
>Counter関数のparamの値を操作します  
>
>```C++
> int change_param(int counter) {
>   switch (count_stopper(mode_reader())) {    // スイッチの値取得
>
>   case 1:                       // スイッチの値が1のとき
>     counter++;                   // counterを1やす 
>     break;
>   case 2:                       // スイッチの値が2で
>     if (counter > 0)              // counterが0以上なら
>       counter--;                   // counterを1減らす
>     break;
>   case 3:                    // スイッチの値が3のとき
>     counter = 0;               // counterを0にする
>     break;
>   }
>   return counter;         // counterの値を返す
> }
>```

## 7セグメントLEDに関するもの

### sevseg_LEDクラス

>数値入力から出力までに必要なデータや、それらを操作する関数を
>一式にまとめているようなものです
>モードをそれぞれ実行する際に宣言されています
>
>```C++
> class sevseg_LED {
>   int head, tale;             // 数値の先頭の桁、最後の桁をクラス宣言時に設定
>   int point;                  // 数点の位置をクラス宣言時に設定
>   double src_number;                // 表示する数値を格納
>   int splited_num[DIGITS_NUM]; 　             // 分割済みの数字の並び(配列)を格納
>   int inteder_ary[DIGITS_NUM][SEGMENT_NUM];   // 数字それぞれにON/OFFを対応させた二次元配列を格納
> public:
>   sevseg_LED(int head);                  // コンストラクタ
>   void set_number(double input_num);      // 数値を設定
>   void split_Numerical_Pos();             // 桁ごとに分割
>   void input_inteder_ary();                 // ON/OFFの並びを対応させる
>   void output_console();              // テスト用関数 説明等は割愛
>   void output_sevseg();                 // 7セグLEDに出力 
>   void set_digit_point(int i);            // 小数点をつける
> };
>```

### class sevseg_LEDのメンバ関数
>
>```C++ 
> sevseg_LED::sevseg_LED(int input_head); 
>```  
>クラスsevseg_LEDのコンストラクタ  
>sevseg_LED型の変数を定義する際に以下の処理がなされます  
>引数に先頭の位を入れてheadを設定、それに応じてpoint, taleも定めます  
>
>```C++
> sevseg_LED::sevseg_LED(int input_head) {
>   head = input_head;                // 先頭の位を設定
>   point = head;                    // 小数点の位置を設定
>   tale = head - DIGITS_NUM;         // 末尾の位を設定
> }
>```
>***********************************************************
>```C++ 
> void sevseg_LED::set_number(double input_num); 
>```  
>表示する数値を設定するだけの関数  
>
>```C++
> void sevseg_LED::set_number(double input_num) {
>   src_number = input_num;      // 表示する数値を設定
> }
>```
>***********************************************************
>```C++ 
> void sevseg_LED::split_Numerical_Pos(); 
>```  
>表示する数値(src_number)を桁ごとに分割する関数  
>桁ごとの数字はint型の配列(splited_num[])に格納されます  
>
>```C++
> void sevseg_LED::split_Numerical_Pos() {
>   int i, j, k = 0;
>   for (i = head; i > tale; i--) {                    // ループするたびにiを先頭の位から末尾の位まで減らしていく
>     for (j = 0; src_number >= powpow(10, i); j++)     // 数値から10のi乗が引けるなら繰り返す
>       src_number -= powpow(10, i);                   // 数値から10のi乗を引く
>     splited_num[k++] = j;                        // 配列のk番目に”何回引けたか”を代入→kを1だけ増やす
>   }
> }
>```
>***********************************************************
>```C++ 
> void sevseg_LED::input_inteder_ary(); 
>```  
>桁ごとの数字に対応するON/OFFの並びをconvert_NUMintoARYから参照して  
>二次元配列(inteder_ary[][])に格納します  
>
>```C++
> void sevseg_LED::input_inteder_ary() {
>   for (int i = 0; i < DIGITS_NUM; i++)                          // i桁目の
>     for (int j = 0; j < SEGMENT_NUM; j++)                          // j番目に
>       inteder_ary[i][j] = convert_NUMintoARY(splited_num[i])[j];     // ON/OFFを参照して代入
> }
>```
>***********************************************************
>```C++ 
> void sevseg_LED::output_sevseg(); 
>```  
>以上の処理が完了した二次元配列(inteder_ary)を  
> output_array(配列表示関数)に代入するだけの関数  
>
>```C++
> void sevseg_LED::output_sevseg() {
>   output_array(inteder_ary);        // 二次元配列を7セグLEDに出力
> }
>```
>***********************************************************
>```C++ 
> void sevseg_LED::set_digit_point(int i); 
>```  
>小数点の操作をする関数です  
>output_array内で一の位を表示をしている時に小数点を点灯させます  
>
>```C++
> void sevseg_LED::set_digit_point(int i) {
> if (i == point) digit_point = 1;         // i番目が小数点の位置と一致したら小数点を点灯
> else digit_point = 0;                // そうでなければ消灯
> }
>```

### その他の関数
>```C++ 
> double powpow(int a, int b); 
>```  
>aのb乗を返す関数  
>split_Numerical_Pos内ではbの部分を1ずつ小さくすることで  
> 10 → 1 → 0.1 のように変化させています  
>
>```C++
> double powpow(int a, int b) {
>   double dest = 1;                                          // 変数destを1で初期化
>   if (b > 0) for (int i = 0; i < b; i++) dest *= (double)a;     // b>0ならbの数だけdestにaをかける
>   if (b < 0) for (int i = 0; i > b; i--) dest /= (double)a;     // b<0ならbの数だけdestをaで割る
>   return dest;                                               // destの値を返す(b==0なら1を返す)
> } 
>```
>***********************************************************
>```C++
> int* convert_NUMintoARY(int element);
>```  
>引数に0~9の数字を入れると、それぞれに対応するON/OFFの配列(の先頭アドレス)を返します  
>0~9以外の数字が入った場合はErr(エラー)を表示します  
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
> int* convert_NUMintoARY(int element) {
>   int sevseg_ary[NUM_PATTERN][SEGMENT_NUM] = {
>  //  [a]  [b]  [c]  [d]  [e]  [f]  [g]
>     {ON,  ON,  ON,  ON,  ON,  ON , OFF}, // for 0
>     {OFF, ON,  ON,  OFF, OFF, OFF, OFF}, // for 1
>     {ON,  ON,  OFF, ON,  ON,  OFF, ON }, // for 2
>     {ON,  ON,  ON,  ON,  OFF, OFF, ON }, // for 3
>     {OFF, ON , ON,  OFF, OFF, ON,  ON }, // for 4
>     {ON,  OFF, ON,  ON,  OFF, ON , ON }, // for 5
>     {ON,  OFF, ON,  ON,  ON,  ON,  ON }, // for 6
>     {ON,  ON,  ON,  OFF, OFF, OFF, OFF}, // for 7
>     {ON,  ON,  ON,  ON,  ON,  ON,  ON }, // for 8
>     {ON,  ON,  ON,  ON,  OFF, ON,  ON }  // for 9
>   };
>   if (element < 0 || 9 < element) Err_message();     // 引数が0~9でなければエラーを表示
>   return sevseg_ary[element];                     // element番目の配列の先頭アドレスを返す
> }
>```
>***********************************************************
>```C++
> void digits_init();
>```  
>7セグLEDを初期化する関数です  
>すべての桁のdigitに1を代入し、消灯させます  
>
>```C++
> void digits_init() {
>   for (int i = 0; i < DIGITS_NUM; i++) digit[i] = 1;    // 全ての桁のカソード側をHighにして消灯
> }
>```
>***********************************************************
>```C++
> void mbedLED_init();
>```  
>mbedに付いているLEDをすべて消灯し初期化する関数です  
>
>```C++
> void mbedLED_init() {
>   for (int i = 0; i < MBED_LED_NUM; i++) mbed_LED[i] = 0;         // mbed_LED全てに0を代入して消灯
> }
>```
>***********************************************************
>```C++ void output_digit(int out_digit[SEGMENT_NUM]); ```  
>桁ひとつぶんを表示する関数です  
>1桁ぶんのON/OFFの配列を受け取って、a~gに順番に代入します  
>
>```C++
> void output_digit(int out_digit[SEGMENT_NUM]) {
>   for (int i = 0; i < SEGMENT_NUM; i++) segment[i] = out_digit[i];   // a~gに配列内のON/OFFを順に代入
> }
>```
>***********************************************************
>```C++
> void output_array(int inteder_array[DIGITS_NUM][SEGMENT_NUM]);
>```  
>ON/OFFの並びを7セグLEDに出力する関数です  
>二次元配列を受け取って表示する桁を切り替えながら  
>output_digit, set_digit_pointをコールします  
>
>```C++
> void output_array(int inteder_array[DIGITS_NUM][SEGMENT_NUM]) {
>   for (int i = 0; i < DIGITS_NUM; i++) {
>     digits_init();                        // 一旦全ての桁を消灯
>     digit[i] = 0;                           // 電流を流す桁を指定
>     output_digit(inteder_array[i]);      // 1桁だけ表示
>     set_digit_point(i);               // 1の位の時は小数点も表示
>     wait(powpow(0.001));                 // 一瞬待つ
>   }
> }
>```

## エラーメッセージに関するもの

>```C++ 
> void Err_message(); 
>```  
>独自の二次元配列を用意してErr(エラー)を表示します  
>
>```C++
> void Err_message() {
>   int error_array[DIGITS_NUM][SEGMENT_NUM] = {
>     {ON,  OFF, OFF, ON,  ON, ON,  ON},
>     {OFF, OFF, OFF, OFF, ON, OFF, ON},          // Err用の配列
>     {OFF, OFF, OFF, OFF, ON, OFF, ON}
>   };
>   while (mode_switcher()) output_array(error_array);  // 上の配列を流し込ん表示で
> }
>```
