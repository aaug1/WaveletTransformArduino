#ifndef DWT_H
#define DWT_H

class DWT {

  public:
    float* h0;
    float* h1;
    int h0_len;
    int h1_len;
    int x_len;
    float* output;
    int ext;
    float* temp;
  
    DWT(float [], float [], int , int );
    ~DWT();
    float* getDWT(float[], int, int);
    //float* geth0(float[], int, int);
    //float* geth1(float[], int, int);

  private:
    void mode1(float* input, int x_len);
    void lphdec(float* x, int n, int mode);
    void dwt1d(float*x, int n, int maxlevel);

};

#endif