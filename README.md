
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

### Development notes for the future!
1. **Dynamic Memory Allocation** It is important to remember that smaller programmable devices such as the Arduino or Teensy have limited memory. Dynamically allocating too much memory, i.e., through a vector data structure, can lead to buggy performance.
2.**Globally scoped values** This was mentioned previously in CSF, but altering globally scoped values can lead to buggy behavior. I believe this especially has to do with how registers work
3. **Be smart about your time** Definitely have a tendency to complete tasks in order, but sometimes that will not be feasible / wise. Make sure to plan your time
4. **Writing code in c++** is a much better idea than just trying to write complicated code on Arduino, especially for beginners, as you can much more easily test code
5. **Passing Arrays** You have to be careful about doing this, especially because it can lead to strange behavior. Sometimes its better to initialize them globally for Arduino, and other times you should pass by reference. Passing by value will potentially cause problems though.


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
