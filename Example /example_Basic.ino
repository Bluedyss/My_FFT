#include "My_FFT.h"

#define N 256  // FFT size
#define A0_PIN A0  // ADC pin for input signal

float real[N];  // Real part of the FFT
float imag[N];  // Imaginary part of the FFT
My_FFT fft(N);  // Create an FFT object

void setup() {
    Serial.begin(115200);
    // Initialize arrays
    for (int i = 0; i < N; i++) {
        real[i] = 0.0;  // Start with a zero signal
        imag[i] = 0.0;
    }
}

void loop() {
    // Sample the analog signal
    for (int i = 0; i < N; i++) {
        real[i] = analogRead(A0_PIN);  // Read the signal from A0
        imag[i] = 0.0;  // Imaginary part is 0 for real signal
        delayMicroseconds(100);  // Delay to simulate sampling rate
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
