#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

#define NUM_STAR_MAIN 3
#define NUM_STAR_SUB 3
const uint8_t STAR_PINS[NUM_STAR_MAIN][NUM_STAR_SUB] = {
    {6, 7, 8},
    {9, 10, 11},
    {21, 22, 23}
};

uint8_t starValues[NUM_STAR_MAIN][NUM_STAR_SUB] = {0};

int tick = 0;

uint8_t outs[30] = {0};

void analogWrite(uint8_t pin, uint8_t value)
{
    outs[pin] = value;
}

void showStars()
{
    for (int i = 0; i < NUM_STAR_MAIN; i++)
        for (int j = 0; j < NUM_STAR_SUB; j++)
            analogWrite(STAR_PINS[i][j], starValues[i][j]);
}

void printStars()
{
    for (int i = 0; i < NUM_STAR_MAIN; i++)
    {
        for (int j = 0; j < NUM_STAR_SUB; j++)
            printf("%d ", starValues[i][j]);
        printf("\n");
    }
            
}

void setStarValue(uint8_t main, uint8_t sub, uint8_t value)
{
    starValues[main][sub] = value;
}

uint8_t getStarValue(uint8_t main, uint8_t sub)
{
    return starValues[main][sub];
}

void setAllStars(uint8_t value)
{
    for (int i = 0; i < NUM_STAR_MAIN; i++)
        for (int j = 0; j < NUM_STAR_SUB; j++)
            setStarValue(i, j, value);
}

#define LOWER 128
#define UPPER 255
#define DECREASE_RATE 1
#define TWINKLE_INTERVAL 2

void twinkleStar()
{
    if (tick == 0) setAllStars(LOWER);

    // Dim every star each tick
    for (int i = 0; i < NUM_STAR_MAIN; i++)
        for (int j = 0; j < NUM_STAR_SUB; j++)
        {
            setStarValue(i, j, getStarValue(i, j) - DECREASE_RATE);
            if (getStarValue(i, j) < LOWER)
                setStarValue(i, j, LOWER);
        }
    
    // Randomly determine which 'star' to twinkle
    if (tick % TWINKLE_INTERVAL == rand() % TWINKLE_INTERVAL)
    {
        setStarValue(rand() % NUM_STAR_MAIN, rand() % NUM_STAR_SUB, UPPER);
    }
}

int main()
{
    srand(time(0));
    while(1)
    {
        twinkleStar();
        printStars();
        tick++;
        cin.get();
    }
}
