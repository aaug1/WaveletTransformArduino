#include "math.h"
#include <iostream>

using namespace std;

class DWT {

  public:
    float* h0;
    float* h1;
    int h0_len;
    int h1_len;
    float* x;
    int x_len;
    int* output;
  
    DWT(float [], float [], int , int );
    float* getDWT(float[], int, int);
    //float* geth0(float[], int, int);
    //float* geth1(float[], int, int);

  private:
    void mode1(float *x, int x_len, float *x_ext, int output_len);
    void lphdec(float *arr, int lphdec_len, float *output, int output_len, int mode);
    void dwt1d();

};

using namespace std;

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
}

float* DWT::getDWT(float input[], int x_len, int maxlevel) {
  x = new float[x_len];
  int ext = trunc((max(h1_len, h0_len))/2.0);
  float* output = new float[ext + x_len + ext];
  // Copy over the input signal
  for (int i = 0; i < x_len; i++) {
    output[i] = input[i];
  }


  

  return output;
}


int main() {
  float h0[] = {0, 1};
  float h1[] = {0, 1};
  float x[] = {0,1,2};

  DWT dwt = DWT(h0, h1, 2,2);

  float* output = dwt.getDWT(x, 3, 2);

  cout << dwt.h0_len << endl;
  cout << x << endl;

  for (int i = 0; i < 3; i++) {
    cout << output[i] << endl;

  }
  
}