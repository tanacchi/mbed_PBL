#include <time.h>
#include <iostream>

int main(void){
  
  time_t timer;
  struct tm *t_st;
  int hour, min;
  int for_sevseg;
  
  t_st = localtime(&timer);
  hour = t_st->tm_hour;
  min = t_st->tm_min;
  for_sevseg = hour * 100 + min;
  
  std::cout << "Hour:" << hour << '\n';
  std::cout << "Minute:" << min << '\n';
  std::cout << "Output:" << for_sevseg << '\n';
   
  return 0;
}
