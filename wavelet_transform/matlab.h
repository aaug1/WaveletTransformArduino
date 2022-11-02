#ifndef MATLAB
#define MATLAB

#include "Arduino.h"

template <class T>
void printArray(T *(&arr), int N) {
  for (int i=0; i < N; i++) {
    Serial.print(arr[i]);
    Serial.print(" ");
  }
  Serial.println();
}

// MATLAB rem function
template <class T>
T remainder(T x, T y) {
  return x - trunc(x / y) * y;
}

template <class T>
void slicing(T *(&arr), int arr_len, T *(&result), int result_len, int X, int Y) {
  for (size_t i = 0; i < (Y - X + 1); i++) {
    result[i] = arr[i + X];
  }
}

// MATLAB fliplr function
// Reverses a vector
template <class T>
void fliplr(T *(&x), int x_len) {
  int j = x_len - 1;
  float temp = 0;
  for (int i = 0; i < (int) x_len / 2; i++) {
    temp = x[i];
    x[i] = x[j];
    x[j] = temp;
    j--;
  }
}

// MATLAB element-wise multiplication
// multiplies elements in a vector provided mult value
template <class T, class U, size_t N>
void elementWiseMult(T (&x)[N], U mult) {
  for (int i = 0; i < N; i++) {
    x[i] *= mult;
  }
}

// MATLAB vector multiplication for 1xM and Mx1
// multiplies elements in a vector
// returns an int, float, double, etc.
template <class T>
T vectorMultiply(T *(&a), int N, T *(&b), int M) {
  if (N != M) {
    Serial.println("error: Vector sizes must be equal!");
    return -1;
  }
  T output = 0;
  for (int i = 0; i < N; i++) {
    output += a[i] * b[i];
  }
  return output;
}

#endif
