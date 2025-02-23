#ifndef MY_FFT_H
#define MY_FFT_H

#include <Arduino.h>

class My_FFT {
public:
    My_FFT(int n);  // Constructor with the FFT size
    void compute(float* real, float* imag);  // Compute FFT

private:
    int N;  // FFT size
    void bitReversal(float* real, float* imag);  // Bit reversal process
    void fftCalculation(float* real, float* imag);  // FFT calculation
};

#endif
