# mbed_PBL

H28年度総合システム工学科後期の必修科目「情報ＰＢＬ」の課題をすべく立ち上げたよ  

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

Name | Description  
--- | ---  
`int* exchange_NUMtoARY(int num);` | int型数値に対応するON/OFFの並び(配列)を吐き出す  
`double get_Temperature(void);` | AnalogInから温度センサーの値を読む  
`int* split_Numerical_Pos(double ondo);` | 3桁のdouble型実数を3列のint型配列に変換  
`void output_7seg(int *src)` | 配列を受け取って 7セグメントLEDに出力  

***
質問とかあったらIssueのところなんかで受け付けてます〜
