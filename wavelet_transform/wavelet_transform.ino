#include "matlab.h"
#include "math.h"

// Input parameters:
// Signal handling
const int x_len = 12;
const int output_len = 12; // ext + x_len + ext;
const int xlh_len = 6; // trunc((10+1)/2);
const int ext = 0; //trunc( max(h0_len, h1_len)/2.0);
// float x[x_len] = { 1, 1, 1, 1, 1, 1,1,1 ,1,1,1,1, 1, 1, 1, 1, 1, 1,1,1 ,1,1,1,1};
// float x[x_len] = { 1, 2,3,4,5,6,7,8,9,10,11,12};
float xl [xlh_len];
float xh [xlh_len];
// Filter specifics
float h0[] = { 1 - sqrt(3)};
float h1[] = { -1/sqrt(2)};
const int h0_len = 1;
const int h1_len = 1;

// Extra (no need to handle these)
float tb = remainder(h0_len, 2);

float x_ext[output_len];
float final_output[output_len];
float temp[x_len];

// Bring definitions to top, for c++ compiler reasons
void lphdec(float *ok, int lphdec_len, int mode);
void dwt1d(int maxlevel);

// Put setup code here, to run before:
void setup() {
  Serial.begin(9600);
}

// Put main code here, to run repeatedly:
void loop() {
  dwt1d(2);

  Serial.println("output");
  printArray(final_output);
  delay(1000);
}


//*********************Extension Types************************//

/**
 * @brief Mode 1: Symmetric Extension
 * 
 * @param x input scaling coefficients, to extend. Either array [1, x_len] or
 * matrix [m, x_len]
 * @param x_len length of x
 * @param ext how much to extend array by; extension size
 * @param tb change extension type for EE- or OO-FB
 */
void mode1(float *x, int x_len, float *x_ext, int output_len, int tb) {
  // x=[fliplr(x(:,1+tb:ext+tb)),x,fliplr(x(:,x_len-ext+1-tb:x_len-tb))];
  float left[ext + 1]; 
  float right[ext + 1];

  int X = tb;
  int Y = ext+tb;
  for (size_t i = 0; i < (Y - X + 1); i++) {
    left[i] = x[i + X];
  }
  X = x_len-ext-tb;
  Y = x_len-tb;
  for (size_t i = 0; i < (Y - X + 1); i++) {
    right[i] = x[i + X];
  }
  fliplr(left); // has length ext
  fliplr(right);

  // copy output into a new x_ext vector
  for (int i = 0; i < ext; i++) {
    x_ext[i] = left[i];
  }
 
  for (int i = 0; i < x_len; i++) {
    x_ext[i+ext] = x[i];
  }
  
  for (int i = 0; i < ext; i++) {
    x_ext[i+2*ext] = right[i];
  }

}

// Mode 2: Circular Extension



// Mode 0: Zero Extension




//*********************lphdec************************//

/**
 * @brief % Decomposition of given scaling coefficients into their scaling and wavelet 
 * parts using a LP PR analysis bank
 * 
 * @param arr input scaling coefficients ([1, x_len] or matrix [m, x_len])
 * @param lphdec_len length of arra ([1, x_len] or matrix [m, x_len])
 * @param mode Extension mode. 
 *        0 - zero extension
 *        1 - symmetric extension
 *        2 - circular convolution
 */
void lphdec(float *arr, int lphdec_len, float *output, int output_len, int mode) {
  if (mode == 1) {
    mode1(arr, lphdec_len, output, output_len, tb);
  }

//  } else if (mode == 2) {
//    mode2(x, ext, tb, x_len);
//  } else {
//    mode0(x, ext, tb, x_len);
//  }
  int s = (h0_len-h1_len) / 2.0;

  int k1, k2 = 0;
  if (s >= 0) {
    k1 = 2 - tb;
    k2 = 2 + s;
  } else {
    k1 = 2 ;
    k2 = 2 - tb - s;
  } 

  int X;
  int Y;
  
  int len = trunc((lphdec_len+1)/2);

  float xl_i[h0_len];
  float xh_i[h1_len];

  
  for (int i = 0; i < len; i++) {
    // Slicing
    X = k1-1;
    Y = k1+h0_len-1;
    for (size_t i = 0; i < (Y - X + 1); i++) {
      xl_i[i] = output[i + X];
    }
    X = k2-1;
    Y = k2+h1_len-1;
    for (size_t i = 0; i < (Y - X + 1); i++) {
      xh_i[i] = output[i + X];
    }
    // Updating values
    xl[i] = vectorMultiply(xl_i, h0);
    xh[i] = vectorMultiply(xh_i, h1);
    k1+=2;
    k2+=2;
  }
}
////*********************dwt1d********************//

/**
 * @brief Forward 1D Discrete Symmetric Biorthogonal Wavelet Transform
 * 
 * @param maxlevel 
 */
void dwt1d(int maxlevel) {
  float output[x_len];

  // Copy over the input signal
  for (size_t i = 0; i < x_len; i++) {
    output[i] = x[i];
  }
  
  float temp[x_len];
  int n = x_len;
  int len = trunc((n+1)/2);

  // Iterate for maxlevel times
  for (int i = 0; i < 2; i++) {
    // Simulates the slice operation
    for (size_t i = 0; i < n; i++) {
      temp[i] = output[i];
    }
   
    // Get xl and xh based on temp
    lphdec(temp, n, output, output_len, 1);

    for (int i = 0; i < len; i++) {
      output[i] = xl[i];
    }
    for (int i = 0; i < len; i++) {
      output[i+len] = xh[i];
    }
    
    n=n/2;
    len = trunc((n+1)/2);

  }

    // Copy over the input signal
  for (size_t i = 0; i < output_len; i++) {
    final_output[i] = output[i];
  }
  

}
