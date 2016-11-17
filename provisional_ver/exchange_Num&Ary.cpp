int* exchange_NUMtoARY(int num){

  int* dest;
  const int 7seg_ary[10][7] = {
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
  
  return dest = 7seg_ary[num];
}
