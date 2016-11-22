int* exchange_NUMtoARY(int num){

  int* dest;
  const int sevseg_ary[10][7] = {
    {ON,  ON,  ON,  ON,  ON,  ON , OFF},
    {OFF, ON,  ON,  OFF, OFF, OFF, OFF},
    {ON,  ON,  OFF, ON,  ON,  OFF, ON },
    {ON,  ON,  ON,  ON,  OFF, OFF, ON },
    {OFF, ON , ON,  OFF, OFF, ON,  ON },
    {ON,  OFF, ON,  ON,  ON,  OFF, ON },
    {ON,  OFF, ON,  ON,  ON,  ON,  ON },
    {ON,  ON,  ON,  OFF, OFF, OFF, OFF},
    {ON,  ON,  ON,  ON,  ON,  ON,  ON },
    {ON,  ON,  ON,  ON,  OFF, ON,  ON }
  };
  
  return dest = sevseg_ary[num];

  // exchange_NUMtoARY(numx)[i]
}
