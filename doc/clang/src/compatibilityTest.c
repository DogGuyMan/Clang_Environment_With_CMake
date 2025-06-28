#include "stdio.h"

int main() {
  float f = 12.34;
  float* fp = &f;
  int* ip = (int*)&f;
  printf("%p : %f\n", fp, *fp);
  printf("%p : %d\n", ip, *ip);
}

/*
./compatibilityTest                 
0x16fbaa32c : 12.340000
0x16fbaa32c : 1095069860
*/