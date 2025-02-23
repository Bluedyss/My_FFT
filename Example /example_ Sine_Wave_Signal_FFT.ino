#include "My_FFT.h"

#define N 256  // FFT size
#define SAMPLING_FREQ 1000  // Sampling frequency (1kHz)
#define SIGNAL_FREQ 50  // Sine wave frequency (50Hz)
#define A0_PIN A0  // ADC pin for input signal

float real[N];  // Real part of the FFT
float imag[N];  // Imaginary part of the FFT
My_FFT fft(N);  // Create an FFT object

void setup() {
    Serial.begin(115200);
}

void loop() {
    // Generate a sine wave
    for (int i = 0; i < N; i++) {
        real[i] = 512 + 512 * sin(2 * PI * SIGNAL_FREQ * i / SAMPLING_FREQ);  // Generate sine wave
        imag[i] = 0.0;  // Imaginary part is 0
        delayMicroseconds(1000);  // Simulate the sampling rate
    }

    // Compute the FFT
    fft.compute(real, imag);

    // Print FFT results
    Serial.println("FFT Spectrum:");
    for (int i = 0; i < N / 2; i++) {  // Print only half of the spectrum
        float magnitude = sqrt(real[i] * real[i] + imag[i] * imag[i]);
        Serial.print("Frequency bin ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(magnitude);
    }

    delay(500);  // Delay before the next FFT computation
}
