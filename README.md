# mbed_PBL

## 12/10 更新しました(下の方に追記)

情報ＰＢＬの課題に取り組む用  

こんな機能あったら良いな〜とか、ここどうなっとるん？みたいなのあったら  
上の方の Issuesから New issue をクリックしてコメントしてね

特に Main/ 内の関数にはなるべくわかりやすいような説明つけてるので良かったら見ていって

***
## 7セグメントLEDの扱いに関する大まかな方針  

7セグメントLEDが「数字入れたらそのまま表示」とかいう生易しいものではなく  
1桁あたりに7つあるLEDそれぞれに ON/OFFの指示をしなければならない~~ちょい面倒な~~ものだったので  
Gグループの作品はこいつの扱いが肝になりそうです。  

今回は温度計をベースに開発して、余力があればオプションを追加していくつもりですが  
いずれにせよ7セグメントLEDを使うので「数字」→「7セグメントLEDに出力」の流れをざっくり説明しときます  

1. 数字を桁ごとに分割(上から3桁)  
2. あらかじめ用意しておいた「数字ごとに対応するa~gのON/OFFの並び」をそれぞれの位の数字に当てはめる  
3. 「1番大きい位のa」~「1番小さい位のg」までのON/OFFを順番にAnalogOutに代入  

これだけで 一応数字は表示されます(小数点とか10の位が0の時とかはまた後で考えます)  
1~3の作業を関数で分割して行っていく感じです  
関数たちの詳しい仕事内容は下の「関数シリーズの説明」とかMain内のソースコードなんかを参照してね  

***
以下リポジトリ内の要素の説明  

Element | Description  
--- | ---  
Main/ | main.cppとテスト済み関数が入ってます  
provisional_ver/ | 関数の草案だの試作品だのが入ってます  
Test/ | provisional_verの中の関数とかを一個ずつTestするときに使用します  
Practice.md | マークダウン記法の練習用。気にしないでくださいな  

***
以下関数シリーズの説明  

### 温度を測って出力

Name | Description  
--- | ---  
`double get_Temperature(void);` | AnalogInから温度センサーの実数値を読む
`int* split_Numerical_Pos(double ondo);` | 読み取ったdouble型実数の上から3桁をint型整数×3の並び(配列)に変換  
`int* exchange_NUMtoARY(int num);` | 桁ごとのint型数値に対応するON/OFFの並び(配列)を吐き出す  
`void output_7seg(int *src)` | ON/OFFの並び(配列)を受け取って 7セグメントLEDに出力(1桁だけ)  

***
## 12/10 更新分

7セグメントLEDのマニュアルが固まってきましたのでざっと下にまとめときます  
**variable**, **data**, **header**は必要に応じて変更する必要があるところです

1. `sevseg_LED variable;`  
   出力するデータごとに~~sevseg_LED型の~~変数を宣言します  
   Jさんの場合は  
   `sevseg_LED hour, sec;`とでもして  
   時・分についてそれぞれ宣言するのが良いでしょう  
2. `variable.set_number(data);`  
   **data**には出力する数値が入ります  
3. `variable.set_head_tale(header);`  
   **header**には「数値が10の何乗代のデータか」を入れてください  
   例えば100~999のデータを出力するときは 2  
   0.1~0.9のときは -1 を*header*のところに入れてください  
4. `variable.split_Numerical_Pos();`  
5. `variable.input_inteder_ary();`  
6. `variable.output_sevseg();`  
   `variable.output_console();`<-テスト用  

あと変更するとしたら`#define`のところの数字かな
***
質問とかあったらIssueのところなんかで受け付けてます〜 (2回目)
