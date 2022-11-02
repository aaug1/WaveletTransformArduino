#include "math.h"
#include <iostream>
#include "matlab.h"
#include "DWT.h"

using namespace std;

int main() {
  float val = 1/sqrt(2);
  float h0[] = {val, val};
  float h1[] = {-val, val};
  //float x[] = {1,2,3,4,5,6,7,8,9,10};
  int x_len = 16;
  float x[] = { 1, 2, 3, 4, 5, 6, 7, 8,9, 10, 11, 12, 13, 14, 15, 16};
  int h0_len = 2;
  int h1_len = 2;
  
  const int ext = trunc( max(h0_len, h1_len)/2.0);
  float* output;

  DWT dwt = DWT(h0, h1,h0_len,h1_len);

  output = dwt.getDWT(x, x_len, 2);

  // cout << dwt.h0_len << endl;
  // cout << x << endl;

  for (int i = 0; i < x_len; i++) {
    cout << output[i] << endl;
  }

}