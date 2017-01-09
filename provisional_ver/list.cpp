int mini_block[][DIGITS_NUM][SEGMENT_NUM] = {
  {
    {OFF, OFF, ON,  ON,  ON,  OFF, ON }, 
    {ON,  ON,  OFF, OFF, OFF, ON,  ON },
    {OFF, OFF, ON,  ON,  ON,  OFF, ON }
  },
  {
    {ON,  ON,  OFF, OFF, OFF, ON,  ON },
    {OFF, OFF, ON,  ON,  ON,  OFF, ON },
    {ON,  ON,  OFF, OFF, OFF, ON,  ON }
  },
  NULL
};

int kunekune[][DIGITS_NUM][SEGMENT_NUM] = {
  {
    {OFF, OFF, ON,  OFF, OFF, ON,  ON },
    {OFF, OFF, ON,  OFF, OFF, ON,  ON },
    {OFF, OFF, ON,  OFF, OFF, ON,  ON }
  },
  {
    {ON,  ON,  OFF, ON,  ON,  OFF, OFF},
    {ON,  ON,  OFF, ON,  ON,  OFF, OFF},
    {ON,  ON,  OFF, ON,  ON,  OFF, OFF}
  },
  {
    {OFF, OFF, ON,  OFF, OFF, ON,  ON },
    {OFF, OFF, ON,  OFF, OFF, ON,  ON },
    {OFF, OFF, ON,  OFF, OFF, ON,  ON }
  },
  {
    {OFF, ON,  OFF, OFF, ON,  OFF, ON },
    {OFF, ON,  OFF, OFF, ON,  OFF, ON },
    {OFF, ON,  OFF, OFF, ON,  OFF, ON }
  },
  {
    {ON,  OFF, ON,  ON,  OFF, ON,  OFF},
    {ON,  OFF, ON,  ON,  OFF, ON,  OFF},
    {ON,  OFF, ON,  ON,  OFF, ON,  OFF}
  },
  {
    {OFF, ON,  OFF, OFF, ON,  OFF, ON },
    {OFF, ON,  OFF, OFF, ON,  OFF, ON },
    {OFF, ON,  OFF, OFF, ON,  OFF, ON }
  },
  NULL
};

int line_though[][DIGITS_NUM][SEGMENT_NUM] = {
  {
    {OFF, OFF, OFF, OFF, ON,  ON,  OFF},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF}
  },
  {
    {OFF, ON,  ON,  OFF, OFF, OFF, OFF},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF}
  },
  {
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {OFF, OFF, OFF, OFF, ON,  ON,  OFF},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF}
  },
  {
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {OFF, ON,  ON,  OFF, OFF, OFF, OFF},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF}
  },
  {
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {OFF, OFF, OFF, OFF, ON,  ON,  OFF}
  },
  {
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {OFF, ON,  ON,  OFF, OFF, OFF, OFF}
  },
  NULL
};
