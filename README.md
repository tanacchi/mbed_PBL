# mbed_PBL

情報ＰＢＬの課題に取り組む用  

こんな機能あったら良いな〜とか、ここどうなっとるん？みたいなのあったら  
上の方の Issuesから New issue をクリックしてコメントしてね

特に Main/ 内の関数にはなるべくわかりやすいような説明つけてるので良かったら見ていって

***
## 7セグメントLEDの扱いに関する大まかな方針  

「数字」→「7セグメントLEDに出力」の流れをざっくり説明しときます  

1. 数字を桁ごとに分割(上から3桁)  
2. 「数字ごとに対応するa~gのON/OFFの並び」をそれぞれの位の数字に当てはめる  
3. a~gまでのON/OFFを桁ごとにAnalogOutに代入  

これだけで 一応数字は表示されます(小数点とか10の位が0の時とかはまた後で考えます)  
1~3の作業を関数で分割して行っていく感じです  
関数たちの詳しい仕事内容は下の「関数シリーズの説明」とかMain内のソースコードなんかを参照してね  

**variable**(変数), **data**(数値), **header**(先頭の桁)は必要に応じて変更する必要があるところです

1. `sevseg_LED variable(header);`  
   出力するデータごとに変数(**variable**)を宣言します  
   **header**には「数値が10の何乗代のデータか」を入れてください  
   例えば100~999のデータを出力するときは 2  
   0.1~0.9のときは -1 を**header**のところに入れてください 
   Jさんの場合は  
   `sevseg_LED time `とか  
2. `variable.set_number(data);`  
   **data**には出力する数値が入ります  
3. `variable.split_Numerical_Pos();`  
4. `variable.input_inteder_ary();`  
5. `variable.output_sevseg();`  
   `variable.output_console();`<-テスト用

上の1~5を無限ループさせたらLEDに出力できるようになってます

***
以下リポジトリ内の要素の説明  

Element | Description  
--- | ---  
Main/ | main.cppとテスト済み関数が入ってます  
Test/ | provisional_verの中の関数とかを一個ずつTestするときに使用します  
for_J_group | Jさんとの共同開発用ディレクトリ  
provisional_ver/ | 関数の草案だの試作品だのが入ってます  
Practice.md | マークダウン記法の練習用。気にしないでくださいな  

************************************************************
以下関数シリーズの説明

## 7セグメントLEDに関するもの

### class sevseg_LEDのメンバ関数

>* `sevseg_LED tmp(1);`
>```C++
>sevseg_LED::sevseg_LED(int input_head){ // head < tale　-> Err!!
>  head = input_head;
>  tale = head - WIDTH;
>}
>```
>
>* `set_number(data);`
>```C++
>void sevseg_LED::set_number(double num){
>  input_number = num;
>}
>```
>
>* `split_Numerical_Pos();`
>```C++
>void sevseg_LED::split_Numerical_Pos(){
>  int i, j, k = 0;
>  input_number += 5 * 10^tale;
>  for (i = head; i > tale; i--){ 
>    for (j = 0; input_number >= powpow(10, i); j++) input_number -= powpow(10, i);
>    splited_num[k++] = j;
>  }
>}
>```
>
>* `input_inteder_ary();`
>```C++
>void sevseg_LED::input_inteder_ary(){
>  for (int i = 0; i < WIDTH; i++)
>    for (int j = 0; j < SEGMENT_NUM; j++)
>      output_array[i][j] = exchange_NUMtoARY(splited_num[i])[j];
>}
>```
>
>* `output_sevseg();`
>```C++
>void sevseg_LED::output_sevseg(){ 
>  for (int i = 0; i < WIDTH; i++){
>    digits_init();
>    digit[i] = 0;
>    output_digit(output_array[i]);
>    wait(0.001);
>  }
>}
>```
### その他

* `powpow(10, i);`
```C++
double powpow(int a, int b){
  double dest = 1;
  if (b > 0) for (int i = 0; i < b; i++) dest *= (double)a;
  if (b < 0) for (int i = 0; i > b; i--) dest /= (double)a;
  return dest;
}
```

* `exchange_NUMtoARY(splited_num[i]);`
```C++
int* exchange_NUMtoARY(int element){
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
  if (element < 0 || 9 < element) err_message();
  return sevseg_ary[element];
}
```

* `digits_init();`
```C++
void digits_init(){
  for (int i = 0; i < WIDTH; i++) digit[i] = 1;
}
```

* `output_digit(output_array);`
```C++
void output_digit(int out_digit[SEGMENT_NUM]){
  for (int i = 0; i < SEGMENT_NUM; i++)
    segment[i] = out_digit[i];  
}
```

## モード選択に関するもの

## 温度計に関するもの

## カウンターに関するもの

## エラーメッセージに関するもの

* `err_message();`
```C++
void err_message(){
  int error_array[3][7] = {
    {ON,  OFF, OFF, ON,  ON, ON,  ON},
    {OFF, OFF, OFF, OFF, ON, OFF, ON},
    {OFF, OFF, OFF, OFF, ON, OFF, ON}
  };
  while (1){
    for (int i = 0; i < WIDTH; i++){
      digits_init();
      digit[i] = 0;
      output_digit(error_array[i]);
      wait(0.001);
    }
  }
}
```

************************************************************
##今後の予定

sevseg_LEDのパッケージ的には既に完成しています  
現在はオプションの開発を進めていく感じです  

「ボタン同時押し判定」「カウントアップ・カウントダウン時の数値表示」  
「現在時刻の取得」なんかが今後の課題ですね  
