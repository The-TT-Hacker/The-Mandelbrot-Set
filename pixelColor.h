#include <math.h>

bits8 stepsToRed(bits8 steps){
   bits8 stepsToRed = 33;
   if(steps >= 15 && steps <= 90) {
      stepsToRed = (bits8) 2.8*steps;
   }
   if(steps < 15) {
      stepsToRed = (bits8) pow(steps, 1.2);
   }
   return stepsToRed;
}

bits8 stepsToGreen(bits8 steps){
   bits8 stepsToGreen = 89;
   if(steps <= 90) {
      stepsToGreen = steps;
   }
   //if(steps < 34) {
   //   stepsToGreen = (bits8) pow(steps, 1.2);
   //}
   return stepsToGreen;
}

bits8 stepsToBlue(bits8 steps){
   bits8 stepsToBlue = 255;
   if(steps <= 90) {
     stepsToBlue = (bits8) pow(steps, 2.45)/255;
   }
   return stepsToBlue;
}