#include "My_FFT.h"

#define N 256  // FFT size (number of samples)
#define SAMPLING_FREQ 2000  // Sampling frequency (2kHz)

#define A0_PIN A0  // ADC pin for input signal

// Frequencies to simulate (in Hz)
float frequencies[] = {20, 60, 100, 200, 500, 1000, 2000, 8000};  
int num_frequencies = sizeof(frequencies) / sizeof(frequencies[0]);

float real[N];  // Real part of the FFT
float imag[N];  // Imaginary part of the FFT
My_FFT fft(N);  // Create an FFT object

void setup() {
    Serial.begin(115200);
    // Initialize arrays
    for (int i = 0; i < N; i++) {
        real[i] = 0.0;
        imag[i] = 0.0;
    }
}

void loop() {
    for (int j = 0; j < num_frequencies; j++) {
        // Generate sine wave for each frequency
        for (int i = 0; i < N; i++) {
            real[i] = 512 + 512 * sin(2 * PI * frequencies[j] * i / SAMPLING_FREQ);  // Generate sine wave for the frequency
            imag[i] = 0.0;  // Imaginary part is 0 for real signal
            delayMicroseconds(1000);  // Simulate sampling rate
        }

        // Compute FFT
        fft.compute(real, imag);

        // Print FFT results
        Serial.print("Frequency: ");
        Serial.print(frequencies[j]);
        Serial.println(" Hz");

        for (int i = 0; i < N / 2; i++) {  // Print only half of the spectrum
            float magnitude = sqrt(real[i] * real[i] + imag[i] * imag[i]);
            Serial.print("Bin ");
            Serial.print(i);
            Serial.print(": ");
            Serial.println(magnitude);
        }

        Serial.println();  // Add an empty line between frequency results
        delay(1000);  // Delay before processing the next frequency
    }
}
