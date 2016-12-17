#define SWITCH_A p??
#define SWITCH_B p??

int starter_switch(){
  int mode = 0;

  for (int i = 0; i < 10^5; i++)
    if (mode = mode_reader() != 0) return mode;

  return mode;
}

int switch_reader(int ch){
  DigitalIn tact_switch[2] = {
    DigitalIn (SWITCH_A),
    DigitalIn (SWITCH_B)
  };
  return tact_switch[ch];
}

int mode_reader(){
  if ((switch_reader[0] == 0) || (switch_reader[1] == 0))
    return 0;
  if ((switch_reader[0] == 1) || (switch_reader[1] == 0))
    return 1;
  if ((switch_reader[0] == 0) || (switch_reader[1] == 1))
    return 2;
  if ((switch_reader[0] == 1) || (switch_reader[1] == 1))
    return 3;
}
