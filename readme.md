# FFT on ESP32

This project demonstrates how to use the Fast Fourier Transform (FFT) on an ESP32 to analyze signals from a microphone or other analog sources. With this implementation, you can sample a signal and identify the intensity of specific frequencies.

## Requirements

- **ESP32** or any other microcontroller compatible with the **Wire** library.
- **Arduino IDE** with the ESP32 framework installed.
- **My_FFT** library for FFT calculation.

## Hardware

- **ESP32** board.
- A microphone module or any other analog input connected to pin A0.

## Installation

1. Download this repository or copy the code into your Arduino IDE.
2. Ensure that the **ESP32** is properly set in your Arduino IDE (**Tools > Board > ESP32 Dev Module**).
3. Make sure you have the **My_FFT** library installed.
4. Connect your microphone or another analog signal to pin **A0** (or change the pin in the code).
5. Upload the code to the ESP32.

## Code

```cpp
#include <Wire.h>
#include "My_FFT.h"

#define A0_PIN 34  // Microphone input
#define N 256  // FFT size
#define SAMPLE_RATE 32000  // 32 kHz sampling rate

float real[N];
float imag[N];

int targetFreqs[] = {20, 60, 100, 200, 500, 1000, 2000, 8000, 10000};
#define NUM_FREQS (sizeof(targetFreqs) / sizeof(targetFreqs[0]))

My_FFT fftProcessor(N);

void setup() {
    Serial.begin(115200);
}

void loop() {
    // 1 Sampling
    for (int i = 0; i < N; i++) {
        real[i] = (analogRead(A0_PIN) / 4095.0) * 3.3 - 1.65;  // Mapping ADC to -1.65 to 1.65 V
        imag[i] = 0.0;
        delayMicroseconds(1000000 / SAMPLE_RATE);
    }

    //  FFT computation using the library
    fftProcessor.compute(real, imag);

    //  Selecting specific frequencies
    int spectrum[NUM_FREQS] = {0};
    for (int j = 0; j < NUM_FREQS; j++) {
        int index = (targetFreqs[j] * N) / SAMPLE_RATE;
        float magnitude = sqrt(real[index] * real[index] + imag[index] * imag[index]) / N;
        spectrum[j] = map(magnitude, 0, 5000, 0, 100);
    }

    //  Output to Serial Monitor
    Serial.println("Frequency | Intensity");
    for (int j = 0; j < NUM_FREQS; j++) {
        Serial.print(targetFreqs[j]);
        Serial.print(" Hz | ");
        Serial.println(spectrum[j]);
    }

    delay(500);
}
