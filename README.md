# mbed_PBL

##説明書です。読んでね

H28年度総合システム工学科後期の必修科目「情報ＰＢＬ」の課題をすべく立ち上げたよ  

こんな機能あったら良いな〜とか、ここどうなっとるん？みたいなのあったら  
上の方の Issuesから New issue をクリックしてコメントしてね

特に Main/ 内の関数にはなるべくわかりやすいような説明つけてるので良かったら見ていって

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
質問とかあったらIssueのところなんかで受け付けてます〜 (2回目)
