#include "My_FFT.h"

My_FFT::My_FFT(int n) {
    this->n = n;
}

void My_FFT::compute(float* real, float* imag) {
    // Předpočítání bitového zrcadlení
    bitReverseSwap(real, imag);
    // Výpočet FFT
    fft(real, imag);
}

void My_FFT::fft(float* real, float* imag) {
    int len, i, j, k;
    float tReal, tImag, uReal, uImag, wReal, wImag, angle;
    
    for (len = 2; len <= n; len <<= 1) {
        angle = -2.0 * M_PI / len;
        wReal = cos(angle);
        wImag = sin(angle);

        for (i = 0; i < n; i += len) {
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

void My_FFT::bitReverseSwap(float* real, float* imag) {
    int i, j, k;
    float tReal, tImag;

    j = 0;
    for (i = 1; i < n; i++) {
        int bit = n >> 1;
        while (j >= bit) {
            j -= bit;
            bit >>= 1;
        }
        j += bit;
        if (i < j) {
            tReal = real[i];
            real[i] = real[j];
            real[j] = tReal;

            tImag = imag[i];
            imag[i] = imag[j];
            imag[j] = tImag;
        }
    }
}
