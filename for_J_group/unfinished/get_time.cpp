#include <time.h>
#include <stdio.h>

int main(void){
  
  time_t timer;
  struct tm *t_st;
  
  t_st = localtime(&timer);
  
  printf("Month:%d\n", t_st->tm_hour);
  printf("Day:%d\n", t_st->tm_min);
  
  return 0;
}
