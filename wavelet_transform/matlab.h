#ifndef MATLAB
#define MATLAB

template <class T, size_t N>
void printArray(T (&arr)[N]) {
  for (auto ele : arr) {
    Serial.print(ele);
    Serial.print(" ");
  }
  Serial.println();
}

// MATLAB rem function
template <class T>
T remainder(T x, T y) {
  return x - trunc(x / y) * y;
}

template <class T, size_t arr_len, size_t result_len>
void slicing(const T (&arr)[arr_len], T (&result)[result_len], int X, int Y) {
  for (size_t i = 0; i < (Y - X + 1); i++) {
    result[i] = arr[i + X];
  }
}

// MATLAB fliplr function
// Reverses a vector
template <class T, size_t x_len>
void fliplr(T (&x)[x_len]) {
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
template <class T, size_t N, size_t M>
T vectorMultiply(T(&a)[N], T(&b)[M]) {
  if (N != M) {
    Serial.println("Vector sizes must be equal!");
    return -1;
  }
  T output = 0;
  for (int i = 0; i < N; i++) {
    output += a[i] * b[i];
  }
  return output;
}

#endif
