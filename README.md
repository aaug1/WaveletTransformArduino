
# Wavelet Transforms:
Author: Aidan Aug
Date: Oct 29, 2022

## Description:

This code is an implementation of the wavelet transform, written for an Arduino.

The implentation makes several assumptions about the input signal:

1. Input signal is 1D
2. The has a simulated signal at the moment. Please update this with Serial.read() values.


Credit to Arik Slepyan for the project proposal!

---
## Additional Notes: 

### Folder descriptions
Please download the wavelet_transform_all repository to run the code. The other file contains code written in PlatformIO, but was used primarily for testing purposes.


### Testing
To make sure code is running properly, paste the following in setup(), Make sure the correct output appears on the serial monitor as you would expect
```
  printArray(x);

  // Test slicing
  slicing(x, result, 2, 2);
  Serial.println("After slicing: ");
  printArray(result);

  // Test fliplr
  fliplr(x);
  printArray(x);

  // test elementwisemult
  elementWiseMult(x, 10.0);
  printArray(x);
  elementWiseMult(x, 0.1);
  printArray(x);

  // test vectorMultiply
  float c[] = { 1, 2, 3}; // 1 + 4 + 9 = 14
  float d[] = { 1, 2, 3};
  int x = vectorMultiply(c, d);
  Serial.println(x);

  Serial.println("MOVE TO LPHDEC");

  //**********TEST LBHDEC*************//
  lphdec(temp, x_len, 1);
  Serial.println("ext_x: ");
  for (int i = 0; i < x_len; i++) {
    Serial.println(ext_x[i]);
  }
  Serial.println("xl");
  for (int i = 0; i < len; i++) {
    Serial.println(xl[i]);
  }
  Serial.println("xh");
  for (int i = 0; i < len; i++) {
    Serial.println(xh[i]);
  }
  ```
