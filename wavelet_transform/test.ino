#include "matlab.h"
#include "math.h"
#include "DWT.h"

float* output;
float val = 1/sqrt(2);
float h0[] = {val, val};
float h1[] = {-val, val};
int x_len = 16;
float x[] = { 1, 2, 3, 4, 5, 6, 7, 8,9, 10, 11, 12, 13, 14, 15, 16};
int h0_len = 2;
int h1_len = 2;

void setup() {
  Serial.begin(9600);

}

void loop() {
  // Initialize dwt object, with specified filter properties
  DWT dwt = DWT(h0, h1,h0_len,h1_len);

  // Calculate
  output = dwt.getDWT(x, x_len, 2);
  Serial.println("The final dwt: ");
  printArray(output, x_len);
  delay(5000);

  /* Example code for reading from sensor: */
  
  // for (int i = 0; i < x_len; i++) {
  //   x[i] = analogRead(A0);
  // }
  // output = dwt.getDWT(x, x_len, 2);
  // Serial.println("The final dwt: ");
  // printArray(output, x_len);
  // delay(5000);
  

}