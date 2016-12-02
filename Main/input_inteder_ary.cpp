void input_inteder_ary(int* fromSplit, int **toOutput);

void input_inteder_ary(int* fromSplit, int **toOutput){
  int i, j;
  for (i = 0; i < 3; i++)
    for (j  = 0; j < 7; j++)
      toOutput[i][j] = exchange_NUMtoARY(fromSplit[i])[j];
}
/*

数値を桁ごとに分けた配列を受け取る
↓
数字ごとにON/OFFの組み合わせの配列を参照する
↓
あらかじめ用意しておいた二次元配列に代入

*/
