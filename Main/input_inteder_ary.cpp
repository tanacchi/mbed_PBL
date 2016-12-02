void input_inteder_ary(int* fromSplit, int **toOutput);

void input_inteder_ary(int* fromSplit, int **toOutput){
  int i, j;
  for (i = 0; i < 3; i++)
    for (j  = 0; j < 7; j++)
      toOutput[i][j] = exchange_NUMtoARY(fromSplit[i])[j];
}
