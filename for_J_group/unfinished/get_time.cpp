#include <stdio.h>
#include <time.h>

int main(){
  struct tm tm;
  time_t t = time(NULL);

  localtime_r(&t, &tm);

  printf("%d:%d", tm.tm_hour, tm.tm_min);
  
  return 0;
}
