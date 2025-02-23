# FFT na ESP32

Tento projekt ukazuje, jak použít Fourierovu transformaci (FFT) na ESP32 pro analýzu signálu z mikrofonu nebo jiného analogového zdroje. Pomocí této implementace můžete snímat signál a zjistit intenzitu konkrétních frekvencí.

## Požadavky

- **ESP32** nebo jiný mikrokontrolér kompatibilní s knihovnou **Wire**.
- **Arduino IDE** s nainstalovaným ESP32 frameworkem.
- Knihovna **My_FFT** pro výpočet FFT.

## Hardware

- **ESP32** deska.
- Mikrofonní modul nebo jakýkoli jiný analogový vstup připojený na pin A0.

## Instalace

1. Stáhněte tento repozitář nebo zkopírujte kód do vaší Arduino IDE.
2. Ujistěte se, že máte správně nastavený **ESP32** v Arduino IDE (přes **Nástroje > Deska > ESP32 Dev Module**).
3. Ujistěte se, že máte nainstalovanou knihovnu **My_FFT**.
4. Připojte váš mikrofon nebo jiný analogový signál k pinu **A0** (nebo změňte pin v kódu).
5. Nahrát kód do ESP32.

## Kód

```cpp
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
