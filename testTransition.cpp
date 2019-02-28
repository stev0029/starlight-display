#include <stdio.h>
#include <iostream>
#include <cstdint>
using namespace std;

#define NUM_PIXELS_1 8
#define NUM_PIXELS_2 8
uint32_t pixels1[NUM_PIXELS_1];
uint32_t pixels2[NUM_PIXELS_2];


int tick = 50;

void riseFallState();
void setPixels();

void printPixels(uint32_t pixels[], int length);
void setColor(uint32_t pixels[], int n, uint32_t color);
uint32_t toHexColor(uint8_t r, uint8_t g, uint8_t b);
uint32_t fadeColor(uint8_t pos);

int main()
{
    while (1)
    {
        riseFallState();
        printPixels(pixels1, NUM_PIXELS_1);
        printPixels(pixels2, NUM_PIXELS_2);
        cin.get();
        // if (tick == duration)
        //     break;
    }
}

bool isRising = true;

void riseFallState()
{
    setPixels();
    if (isRising)
        tick--;
    else
        tick--;
}

#define DURATION_1 32
#define DURATION_2 16

#define INITIAL 0xffffff
#define FINAL 0x000000

void setFadingEffect(uint32_t pixels[], int length, int pos, int duration)
{
    int period = duration / length;
    for (int i = 0; i < length; i++)
    {
        uint32_t color;
        if (i < pos / period)
            color = FINAL;
        else if (i == pos / period)
            color = fadeColor((pos % period * 256 / period));
        else
            color = INITIAL;
        setColor(pixels, i, color);
    }
}

void setFinal(uint32_t pixels[], int length)
{
    for (int i = 0; i < length; i++)
    {
        setColor(pixels, i, FINAL);
    }
}

void setInitial(uint32_t pixels[], int length)
{
    for (int i = 0; i < length; i++)
    {
        setColor(pixels, i, INITIAL);
    }
}

void setPixels()
{
    int pos = tick;

    if (pos < DURATION_1)
    {
        setFadingEffect(pixels1, NUM_PIXELS_1, pos, DURATION_1);
        setInitial(pixels2, NUM_PIXELS_2);
    }
    else if (pos < DURATION_1 + DURATION_2)
    {
        pos -= DURATION_1;

        setFinal(pixels1, NUM_PIXELS_1);
        setFadingEffect(pixels2, NUM_PIXELS_2, pos, DURATION_2);
    }
    else 
    {
        setFinal(pixels1, NUM_PIXELS_1);
        setFinal(pixels2, NUM_PIXELS_2);
    }

}

uint32_t fadeColor(uint8_t pos)
{
    uint32_t val = INITIAL - FINAL;

    uint8_t r = ((val & 0xff0000) >> 16) * (256 - pos) / 256;
    uint8_t g = ((val & 0x00ff00) >> 8) * (256 - pos) / 256;
    uint8_t b = (val & 0x0000ff) * (256 - pos) / 256;

    return (r << 16) + (g << 8) + b;
}



void printPixels(uint32_t pixels[], int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%06x ", pixels[i]);
    }
    printf("\n");
}

void setColor(uint32_t pixels[], int n, uint32_t color)
{
    pixels[n] = color;
}

uint32_t toHexColor(uint8_t r, uint8_t g, uint8_t b)
{
    return (r << 16) + (g << 8) + b;
}
