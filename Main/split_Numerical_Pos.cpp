double powpow(int a, int b){  // aの b乗をdouble型実数で返す
  double dest = 1;
  int i;
  
  if (b > 0)
    for (i = 0; i < b; i++) dest *= (double)a;
  else (b < 0)
    for (i = 0; i > b; i--) dest /= (double)a;
   
  return dest;
}

int* split_Numerical_Pos(double dd){ // double型実数を上から３桁読んで int型整数×3の並び(配列)にして出力
  int ary[3] = {};
  int *dest_num = ary;
  int  i, j;

  dd += 0.05; // 小数点第一位までを上から読むので0.05を足すことにより四捨五入出来る
  
  for (i = 1; i > -2; i--){ // { i | 1 → -1 } 温度センサの値ddから10のi乗を引き dd < 10^iになったらiの値を進める
    for (j = 0; dd >= powpow(10, i); j++) 
      dd -=powpow(10, i);
    ary[1-i] = j;　// 配列に何回引いたかを記録
  }
  return dest_num;
}
