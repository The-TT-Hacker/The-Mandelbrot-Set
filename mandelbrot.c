#include "mandelbrot.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>


#define BYTES_PER_PIXEL 3
#define BITS_PER_PIXEL (BYTES_PER_PIXEL*8)
#define NUMBER_PLANES 1
#define PIX_PER_METRE 2835
#define MAGIC_NUMBER 0x4d42
#define NO_COMPRESSION 0
#define OFFSET 54
#define DIB_HEADER_SIZE 40
#define NUM_COLORS 0
 
#define SIZE 512


#define MAX_STEPS 256

#define BMP_FILE "mandelbrot.bmp"

typedef struct _complexNo complexNo;

typedef unsigned char  bits8;
typedef unsigned short bits16;
typedef unsigned int   bits32;


struct _complexNo {
   double re;
   double im;
};

void writeHeader (FILE *file);

complexNo compute(complexNo z, complexNo c);

int stepsToEscape(complexNo z, complexNo c);

int main(int argc, char *argv[]) {

   assert(sizeof(bits8) == 1);
   assert(sizeof(bits16) == 2);
   assert(sizeof(bits32) == 4);

   FILE *outputFile;

   outputFile = fopen(BMP_FILE, "wb");
   assert((outputFile != NULL) && "Cannot open file");

   writeHeader(outputFile);   

   double x = 0;
   double y = 0;
   double zoom = 0;

   printf("Enter your desired zooooom level: (suggested min 2)");
   scanf("%lf", &zoom);

   bits8 byte;

   while (y < SIZE) {
      while (x < SIZE) {
         printf("x: %lf, y: %lf\n", x, y);
         complexNo z;
         z.re = 0;
         z.im = 0;

         complexNo c;
         c.re = x/pow(10, zoom) - (double) SIZE/pow(10, zoom)/2 + pow(1/2, zoom);
         c.im = y/pow(10, zoom) - (double) SIZE/pow(10, zoom)/2 + pow(1/2, zoom);

         byte = 255 - stepsToEscape(z, c);

         //printf("Byte is: %d\n", byte);

         fwrite (&byte, sizeof byte, 1, outputFile);
         fwrite (&byte, sizeof byte, 1, outputFile);
         fwrite (&byte, sizeof byte, 1, outputFile);

         x++;

      }
      x = 0;
      y++;
   }


   return EXIT_SUCCESS;
}

complexNo compute(complexNo z, complexNo c) {

   double real = z.re * z.re - z.im * z.im + c.re;
   double imaginary = 2 * z.re * z.im + c.im;

   z.re = real;
   z.im = imaginary;

   return z;
}

int stepsToEscape(complexNo z, complexNo c) {

   int steps = 1;

   z = compute(z, c);

   //printf("z = %lf + %lfi\n |z|^2 = %lf\n", z.re, z.im, z.re * z.re + z.im * z.im);

   while (z.re * z.re + z.im * z.im <= 4 && steps < MAX_STEPS) {
      //printf("steps: %d\n", steps);
      z = compute(z, c);
      //printf("z%d = %lf + %lfi\n |z|^2 = %lf\n", steps, z.re, z.im, z.re * z.re + z.im * z.im);
      steps++;

   }
   //printf("steps to return: %d", steps);
   return steps;
}

void writeHeader (FILE *file) {
   assert(sizeof (bits8) == 1);
   assert(sizeof (bits16) == 2);
   assert(sizeof (bits32) == 4);
 
   bits16 magicNumber = MAGIC_NUMBER;
   fwrite (&magicNumber, sizeof magicNumber, 1, file);
 
   bits32 fileSize = OFFSET + (SIZE * SIZE * BYTES_PER_PIXEL);
   fwrite (&fileSize, sizeof fileSize, 1, file);
 
   bits32 reserved = 0;
   fwrite (&reserved, sizeof reserved, 1, file);
 
   bits32 offset = OFFSET;
   fwrite (&offset, sizeof offset, 1, file);
 
   bits32 dibHeaderSize = DIB_HEADER_SIZE;
   fwrite (&dibHeaderSize, sizeof dibHeaderSize, 1, file);
 
   bits32 width = SIZE;
   fwrite (&width, sizeof width, 1, file);
 
   bits32 height = SIZE;
   fwrite (&height, sizeof height, 1, file);
 
   bits16 planes = NUMBER_PLANES;
   fwrite (&planes, sizeof planes, 1, file);
 
   bits16 bitsPerPixel = BITS_PER_PIXEL;
   fwrite (&bitsPerPixel, sizeof bitsPerPixel, 1, file);
 
   bits32 compression = NO_COMPRESSION;
   fwrite (&compression, sizeof compression, 1, file);
 
   bits32 imageSize = (SIZE * SIZE * BYTES_PER_PIXEL);
   fwrite (&imageSize, sizeof imageSize, 1, file);
 
   bits32 hResolution = PIX_PER_METRE;
   fwrite (&hResolution, sizeof hResolution, 1, file);
 
   bits32 vResolution = PIX_PER_METRE;
   fwrite (&vResolution, sizeof vResolution, 1, file);
 
   bits32 numColors = NUM_COLORS;
   fwrite (&numColors, sizeof numColors, 1, file);
 
   bits32 importantColors = NUM_COLORS;
   fwrite (&importantColors, sizeof importantColors, 1, file);
 
}
