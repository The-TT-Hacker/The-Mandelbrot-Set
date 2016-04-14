#include "mandelbrot.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _complexNo complexNo;

struct _complexNo {
   double re;
   double im;
}

int main(int argc, char *argc[]) {

   complexNo z;
   z.re = 2;
   z.im = -3;

   printf("Z is: %lf + %lfi \n", z.re, z.im);

   return EXIT_SUCCESS;
}
