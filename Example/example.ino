#include <Wire.h>
#include "My_FFT.h"

#define A0_PIN 34  // Mikrofonní vstup
#define N 256  // FFT velikost
#define SAMPLE_RATE 32000  // 32 kHz vzorkovací frekvence

float real[N];
float imag[N];

int targetFreqs[] = {20, 60, 100, 200, 500, 1000, 2000, 8000, 10000};
#define NUM_FREQS (sizeof(targetFreqs) / sizeof(targetFreqs[0]))

My_FFT fftProcessor(N);

void setup() {
    Serial.begin(115200);
}

void loop() {
    // 1️⃣ Vzorkování
    for (int i = 0; i < N; i++) {
        real[i] = (analogRead(A0_PIN) / 4095.0) * 3.3 - 1.65;  // Mapování ADC na -1.65 až 1.65 V
        imag[i] = 0.0;
        delayMicroseconds(1000000 / SAMPLE_RATE);
    }

    // 2️⃣ Výpočet FFT pomocí knihovny
    fftProcessor.compute(real, imag);

    // 3️⃣ Výběr konkrétních frekvencí
    int spectrum[NUM_FREQS] = {0};
    for (int j = 0; j < NUM_FREQS; j++) {
        int index = (targetFreqs[j] * N) / SAMPLE_RATE;
        float magnitude = sqrt(real[index] * real[index] + imag[index] * imag[index]) / N;
        spectrum[j] = map(magnitude, 0, 5000, 0, 100);
    }

    // 4️⃣ Výpis do Serial Monitoru
    Serial.println("Frekvence | Síla");
    for (int j = 0; j < NUM_FREQS; j++) {
        Serial.print(targetFreqs[j]);
        Serial.print(" Hz | ");
        Serial.println(spectrum[j]);
    }

    delay(500);
}
