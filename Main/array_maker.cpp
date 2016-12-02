void array_maker(double dd, int* toInput);

void array_maker(double dd, int* toInput){
  int i;
  for (i = 0; i < 3; i++) toInput[i] = split_Numerical_Pos(dd)[i];
}
/*

センサーの受け取る
↓
桁ごとに分割
↓
あらかじめ用意してた配列に代入

*/



