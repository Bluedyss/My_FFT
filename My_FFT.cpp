#include "My_FFT.h"
#include <math.h>

My_FFT::My_FFT(int n) {
    N = n;  // Initialize FFT size
}

void My_FFT::compute(float* real, float* imag) {
    bitReversal(real, imag);  // Perform bit reversal step
    fftCalculation(real, imag);  // Perform FFT calculation
}

void My_FFT::bitReversal(float* real, float* imag) {
    int i, j, bit, len;
    float tempReal, tempImag;
    
    j = 0;
    for (i = 1; i < N; i++) {
        bit = N >> 1;
        while (j >= bit) {
            j -= bit;
            bit >>= 1;
        }
        j += bit;

        if (i < j) {
            // Swap real parts
            tempReal = real[i];
            real[i] = real[j];
            real[j] = tempReal;

            // Swap imaginary parts
            tempImag = imag[i];
            imag[i] = imag[j];
            imag[j] = tempImag;
        }
    }
}

void My_FFT::fftCalculation(float* real, float* imag) {
    int len, step, i, j;
    float angle, wReal, wImag, uReal, uImag, tReal, tImag;

    for (len = 2; len <= N; len <<= 1) {
        angle = -2.0 * PI / len;
        wReal = cos(angle);
        wImag = sin(angle);

        for (i = 0; i < N; i += len) {
            uReal = 1.0;
            uImag = 0.0;

            for (j = 0; j < len / 2; j++) {
                int i1 = i + j;
                int i2 = i + j + len / 2;

                tReal = uReal * real[i2] - uImag * imag[i2];
                tImag = uReal * imag[i2] + uImag * real[i2];

                real[i2] = real[i1] - tReal;
                imag[i2] = imag[i1] - tImag;
                real[i1] += tReal;
                imag[i1] += tImag;

                tReal = uReal * wReal - uImag * wImag;
                uImag = uReal * wImag + uImag * wReal;
                uReal = tReal;
            }
        }
    }
}

