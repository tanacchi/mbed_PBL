void output_Temperature(int **src);

void output_Temperature(int **src){
  int i;
  for (i = 0; i < 3; i++) output_sevseg(src[i]);
}
