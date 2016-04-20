#include "frequencyScaling.h"

// First half of this array is previous sample set
// Second half of this array is current sample set
short inputBuffer[ARRAY_SIZE * 2];

float windowedCrossSampleArray[ARRAY_SIZE];
float windowedInputArray[ARRAY_SIZE];

/* Store results of windowed frequency scaling in alternating buffers */
float frequencyScaledSamples[3][ARRAY_SIZE];

float hanningWindow[ARRAY_SIZE];

float frequencyScalars[ARRAY_SIZE];

kiss_fft_cfg fft_cfg;
kiss_fft_cfg ifft_cfg;

void configureFft()
{
    fft_cfg = kiss_fft_alloc(ARRAY_SIZE, 0, NULL, NULL);
    ifft_cfg = kiss_fft_alloc(ARRAY_SIZE, 1, NULL, NULL);
}

void configureScalars(float *input)
{
    int i;
    
    for (i = 0; i < ARRAY_SIZE; i++)
    {
        frequencyScalars[i] = input[i];
    }
}

void configureWindow()
{
    int i;
    
    for (i = 0; i < ARRAY_SIZE; i++)
    {
        hanningWindow[i] = 0.5 * (1 - cos((2 * PI * i) / (ARRAY_SIZE - 1)));
    }
}

void applyWindow(short *input, float *output)
{
    int i;

    for (i = 0; i < ARRAY_SIZE; i++)
    {
        output[i] = input[i] * hanningWindow[i];
    }
}

// Applies the FFT-scale-IFFT algorithm to an input array 
// Also applies window before frequency scaling
void frequencyScale(float *input, float *output, int len, float *scalars)
{
    int i;
    kiss_fft_cpx inputComplex[len];
    kiss_fft_cpx transformedArray[len];

    for (i = 0; i < len; i++)
    {
        inputComplex[i].r = input[i];
        inputComplex[i].i = 0;
    }

    kiss_fft(fft_cfg, inputComplex, transformedArray);

    for (i = 0; i < ARRAY_SIZE; i++)
    {
        transformedArray[i].r *= scalars[i];
        transformedArray[i].i *= scalars[i];
    }

    kiss_fft(ifft_cfg, transformedArray, inputComplex);

    for (i = 0; i < ARRAY_SIZE; i++)
    {
        output[i] = inputComplex[i].r / (1.0 * ARRAY_SIZE);
    }
}

// Note: this function will have half-buffer phase shift effect
void processInput(short *input, short *output)
{
    int i;

    // Read in the input buffer
    for (i = 0; i < ARRAY_SIZE; i++)
    {
        inputBuffer[ARRAY_SIZE + i] = input[i];
    }

    // Apply windows to the midpoint buffer and input buffer
    applyWindow(inputBuffer + (ARRAY_SIZE / 2), windowedCrossSampleArray);
    applyWindow(inputBuffer + ARRAY_SIZE, windowedInputArray);

    frequencyScale(windowedCrossSampleArray, frequencyScaledSamples[1], ARRAY_SIZE, frequencyScalars);
    frequencyScale(windowedInputArray, frequencyScaledSamples[2], ARRAY_SIZE, frequencyScalars);

    // Sum overlaps to produce the output array
    for (i = 0; i < ARRAY_SIZE / 2; i++)
    {
        output[i] = frequencyScaledSamples[FSS_PREVIOUS_INPUT][ARRAY_SIZE / 2 + i] + frequencyScaledSamples[FSS_CROSS_INPUT][i];
    }

    for (i = ARRAY_SIZE / 2; i < ARRAY_SIZE; i++)
    {
        // float -> short conversion should be handled automatically
        output[i] = frequencyScaledSamples[FSS_CROSS_INPUT][i] + frequencyScaledSamples[FSS_THIS_INPUT][i - (ARRAY_SIZE / 2)];
    }

    // Store input and scaled version of input for use in next iteration
    for (i = 0; i < ARRAY_SIZE; i++)
    {
        inputBuffer[i] = inputBuffer[i + ARRAY_SIZE];
        frequencyScaledSamples[FSS_PREVIOUS_INPUT][i] = frequencyScaledSamples[FSS_THIS_INPUT][i];
    }
}
