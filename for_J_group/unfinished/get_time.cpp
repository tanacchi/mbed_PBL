#include <time.h>
#include <stdio.h>

int main(void){
  
  time_t timer;
  struct tm *t_st;
  
  t_st = localtime(&timer);
  
  printf("Month:%d\n", t_st->tm_mon+1);
  printf("Day:%d\n", t_st->tm_mday);
  
  return 0;
}
