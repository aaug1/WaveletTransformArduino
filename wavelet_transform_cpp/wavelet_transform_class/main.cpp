#include "math.h"
#include <iostream>
#include "matlab.h"

using namespace std;

class DWT {

  public:
    float* h0;
    float* h1;
    int h0_len;
    int h1_len;
    int x_len;
    float* output;
    int ext;
    float* xl;
    float* xh;
  
    DWT(float [], float [], int , int );
    ~DWT();
    float* getDWT(float[], int, int);
    //float* geth0(float[], int, int);
    //float* geth1(float[], int, int);

  private:
    void mode1(float* input, int x_len);
    void lphdec(float* x, int n, int mode);
    void dwt1d();

};

DWT::DWT(float h0_in[], float h1_in[], int h0_len_in, int h1_len_in) {
  h0_len = h0_len_in;
  h0 = new float[h0_len];
  for (int i = 0; i < h0_len; i++) {
    h0[i] = h0_in[i];
  }

  h1 = new float[h1_len];

  h1_len = h1_len_in;
  for (int i = 0; i < h1_len; i++) {
    h1[i] = h1_in[i];
  }
  ext = trunc( max(h0_len, h1_len)/2.0);

  output = new float[1];
}

DWT::~DWT() {
  delete[] h0;
  delete[] h1;
  delete[] output;
}

float* DWT::getDWT(float input[], int input_len, int maxlevel) {
  // Free and reassign memory
  delete[] output;
  output = new float[ext + input_len + ext];

  mode1(input, input_len);
  lphdec(input, input_len, 1);

  return output;
}

void DWT::mode1(float* x, int x_len) {
  // x=[fliplr(x(:,1+tb:ext+tb)),x,fliplr(x(:,x_len-ext+1-tb:x_len-tb))];
  int len = trunc((x_len+1)/2);
  float* left = new float[len]; 
  float* right = new float[len];
  int tb = remainder(h0_len, 2);

  // create left array
  int X = tb;
  int Y = ext+tb;
  slicing(x, x_len, left, ext, X, Y);
  fliplr(left, ext);

  X = x_len-ext-tb;
  Y = x_len-tb;
  slicing(x, x_len, right, ext, X, Y);
  fliplr(right, ext);

  // copy output into a output vector
  for (int i = 0; i < ext; i++) {
    output[i] = left[i];
  }
 
  for (int i = 0; i < x_len; i++) {
    output[i+ext] = x[i];
  }
  
  for (int i = 0; i < ext; i++) {
    output[i+x_len+ext] = right[i];
  }

  delete[] left;
  delete[] right;
}

void DWT::lphdec(float* x, int n, int mode) {
  if (mode == 1) {
    mode1(x, n);
  }
  int tb = remainder(h0_len, 2);
  int s = (h0_len-h1_len) / 2.0;
  int k1, k2 = 0;
  if (s >= 0) {
    k1 = 2 - tb;
    k2 = 2 + s;
  } else {
    k1 = 2;
    k2 = 2 - tb - s;
  } 

  int X;
  int Y;
  
  int len = trunc((n+1)/2);

  float* xl_i = new float[h0_len];
  float* xh_i = new float[h1_len];
  float* xl = new float[len];
  float* xh = new float [len];
  int output_len = n + 2*ext;

  for (int i = 0; i < len; i++) {
    // Slicing
    X = k1-1;
    Y = k1+h0_len-1;
    slicing(output, output_len, xl_i, h0_len, X, Y);
    X = k2-1;
    Y = k2+h1_len-1;
    slicing(output, output_len, xh_i, h1_len, X, Y);

    // Updating values
    xl[i] = vectorMultiply(xl_i, h0_len, h0, h0_len);
    xh[i] = vectorMultiply(xh_i, h1_len, h1, h1_len);;
    k1+=2;
    k2+=2;
  }

  for (int i = 0; i < len; i++) {
    output[i] = xl[i];
  }

  for (int i = 0; i < len; i++) {
    output[i+len] = xh[i];
  }

  delete[] xl_i;
  delete[] xh_i;
  delete[] xl;
  delete[] xh;
}


int main() {
  float val = 1/sqrt(2);
  float h0[] = {val, val};
  float h1[] = {-val, val};
  float x[] = {1,2,3,4,5,6,7,8,9,10};
  int h0_len = 2;
  int h1_len = 2;
  int x_len = 10;
  const int ext = trunc( max(h0_len, h1_len)/2.0);
  float* output;

  DWT dwt = DWT(h0, h1,h0_len,h1_len);

  output = dwt.getDWT(x, x_len, 1);

  // cout << dwt.h0_len << endl;
  // cout << x << endl;

  for (int i = 0; i < x_len; i++) {
    cout << output[i] << endl;
  }
}