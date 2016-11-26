void array_maker(double dd);

void array_maker(double dd, int* toInput){
  int i;
  for (i = 0; i < 3; i++) toInput[i] = split_Numerical_Pos(dd)[i];
}
