#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>

int main() {
  char buff[2048];
  memset(buff, '\0', sizeof(buff));

  FILE *fptr = fopen("models.txt", "w");
  setvbuf(fptr, buff, _IOLBF, 2048);

  long double mean = 0.01521441214563;
  fprintf(fptr, "Mean : %0.10Lf\n", mean);
  
  fclose(fptr);
  return 0;
}
