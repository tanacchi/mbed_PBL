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

***
以下関数シリーズの説明  

* `void Thermometer();`

```C++
void Thermometer(){
  double data;
  sevseg_LED tmp(1);

  while (1){
    data = tmp_stopper();
    tmp.set_number(data);
    tmp.split_Numerical_Pos();
    tmp.input_inteder_ary();
    tmp.output_sevseg();
  }
}
```

* `double get_Temperature();`

```C++
double get_Temperature(){
  AnalogIn mysensor(TMP_SENSOR_PIN);
  double replyed_vol = mysensor * MBED_VOLTAGE;
  return replyed_vol * 100;
}
```
*``

```C++
double tmp_stopper(){
  static double stock;
  static int i - 1;
  if (i > 10^5) i = 0;
  //  return (i++ == 0) ? stock : stock = get_Temperature();
  i++;
  if (i == 0) return stock = get_Temperature();
  else return stock;
}
```
```C++
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
```
```C++

```

***
##今後の予定

sevseg_LEDのパッケージ的には既に完成しています  
現在はオプションの開発を進めていく感じです  

「ボタン同時押し判定」「カウントアップ・カウントダウン時の数値表示」  
「現在時刻の取得」なんかが今後の課題ですね  

配列の幅を入力値で変化させられたらいいなとか  
headとtaleも勝手に判断してくれるようになればいいなとかいうのも  
ちょっとずつ叶えていくつもり
