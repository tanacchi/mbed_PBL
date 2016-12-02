#define ON 1
#define OFF 0

int* exchange_NUMtoARY(int num){
  // 引数のint型整数に対応するON/OFFの並び(配列)を渡してくれる

  int* dest;
  const int sevseg_ary[10][7] = {
    //a    b    c    d    e    f    g
    {ON,  ON,  ON,  ON,  ON,  ON , OFF}, // for 0
    {OFF, ON,  ON,  OFF, OFF, OFF, OFF}, // for 1
    {ON,  ON,  OFF, ON,  ON,  OFF, ON }, // for 2
    {ON,  ON,  ON,  ON,  OFF, OFF, ON }, // for 3
    {OFF, ON , ON,  OFF, OFF, ON,  ON }, // for 4
    {ON,  OFF, ON,  ON,  ON,  OFF, ON }, // for 5
    {ON,  OFF, ON,  ON,  ON,  ON,  ON }, // for 6
    {ON,  ON,  ON,  OFF, OFF, OFF, OFF}, // for 7
    {ON,  ON,  ON,  ON,  ON,  ON,  ON }, // for 8
    {ON,  ON,  ON,  ON,  OFF, ON,  ON }  // for 9
  };
  // ON = 1  // OFF = 0 
  
  return dest = sevseg_ary[num];

  // exchange_NUMtoARY(num)[i]
}
