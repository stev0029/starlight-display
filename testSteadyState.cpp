#include <stdio.h>
#include <iostream>
#include <cstdint>
using namespace std;

#define NUM_PIXELS 16
uint32_t pixels[NUM_PIXELS];

int tick = 0;
int duration = 8;
int rainbowPeriod = 8;

void setPixels();
void printPixels();
void setColor(int, uint32_t);
uint32_t toHexColor(uint8_t r, uint8_t g, uint8_t b);
uint32_t wheel(uint8_t pos);

int main()
{
    while (1)
    {
        setPixels();
        printPixels();
        cin.get();
        tick++;
        // if (tick == duration)
        //     break;
    }
}

void setPixels()
{
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        uint32_t val = wheel(i * 256 / rainbowPeriod + tick * 256 / duration);
        setColor(i, val);
    }
}

void printPixels()
{
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        printf("%06x ", pixels[i]);
    }
    printf("\n");
}

void setColor(int n, uint32_t color)
{
    pixels[n] = color;
}

uint32_t toHexColor(uint8_t r, uint8_t g, uint8_t b)
{
    return (r << 16) + (g << 8) + b;
}

uint32_t wheel(uint8_t pos) {
    if (pos < 85)
    {
        return toHexColor(255 - pos * 3, pos * 3, 0);
    }
    else if (pos < 170)
    {
        pos -= 85;
        return toHexColor(0, 255 - pos * 3, pos * 3);
    }
    else
    {
        pos -= 170;
        return toHexColor(pos * 3, 0, 255 - pos * 3);
    }
}