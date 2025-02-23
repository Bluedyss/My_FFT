#ifndef MY_FFT_H
#define MY_FFT_H

#include <math.h>

class My_FFT {
public:
    My_FFT(int n);
    void compute(float* real, float* imag);
    
private:
    int n;  // Počet vzorků (musí být mocnina 2)
    void fft(float* real, float* imag);
    void bitReverseSwap(float* real, float* imag);
};

#endif
