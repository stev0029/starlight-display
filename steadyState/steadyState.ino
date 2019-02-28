// ------------------------------- Pin declaration ----------------------------

// 3 City LED strips, each strip 41 pixels
#define CITY_NUM_PIXELS 41
#define NUM_OF_CITY 3
#define CITY_1_PIN 0
#define CITY_2_PIN 1
#define CITY_3_PIN 2

// 3 Base LED strips, each strip 21 pixels
#define BASE_NUM_PIXELS 21
#define NUM_OF_BASE 3
#define BASE_1_PIN 3
#define BASE_2_PIN 4
#define BASE_3_PIN 5

// Starlight pins, individual LEDs
#define NUM_STAR_MAIN 3
#define NUM_STAR_SUB 3
const uint8_t STAR_PINS[NUM_STAR_MAIN][NUM_STAR_SUB] = {
    {6, 7, 8},
    {9, 10, 11},
    {A3, A4, A5}
};

// Ultrasonic sensor
#define TRIG_PIN A0
#define ECHO_PIN A1





// ------------------------- Declaration of strips ----------------------------
// --------- cityStrips[], baseStrips[], initStrips(), showStrips() -----------

#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel cityStrips[] = {
    Adafruit_NeoPixel(CITY_NUM_PIXELS, CITY_1_PIN, NEO_RGB + NEO_KHZ800),
    Adafruit_NeoPixel(CITY_NUM_PIXELS, CITY_2_PIN, NEO_RGB + NEO_KHZ800),
    Adafruit_NeoPixel(CITY_NUM_PIXELS, CITY_3_PIN, NEO_RGB + NEO_KHZ800)
};

Adafruit_NeoPixel baseStrips[] = {
    Adafruit_NeoPixel(BASE_NUM_PIXELS, BASE_1_PIN, NEO_RGB + NEO_KHZ800),
    Adafruit_NeoPixel(BASE_NUM_PIXELS, BASE_2_PIN, NEO_RGB + NEO_KHZ800),
    Adafruit_NeoPixel(BASE_NUM_PIXELS, BASE_3_PIN, NEO_RGB + NEO_KHZ800)
};

void initStrips()
{
    for (int i = 0; i < NUM_OF_CITY; i++)
    {
        cityStrips[i].begin();
    }

    for (int i = 0; i < NUM_OF_BASE; i++)
    {
        baseStrips[i].begin();
    }
}

void showStrips()
{
    for (int i = 0; i < NUM_OF_CITY; i++)
    {
        cityStrips[i].show();
    }

    for (int i = 0; i < NUM_OF_BASE; i++)
    {
        baseStrips[i].show();
    }
}





// ------------------------- Star LED Interface -------------------------------

// Stores the values / brightness (0-255) of the individual LED in a 2D array
// `showStars()` to actually write the values to the pins
// Other functions are getters and setters to access the 2D array

uint8_t starValues[NUM_STAR_MAIN][NUM_STAR_SUB] = {0};

void setStarValue(uint8_t main, uint8_t sub, uint8_t value)
{
    starValues[main][sub] = value;
}

uint8_t getStarValue(uint8_t main, uint8_t sub)
{
    return starValues[main][sub];
}

void showStars()
{
    for (int i = 0; i < NUM_STAR_MAIN; i++)
        for (int j = 0; j < NUM_STAR_SUB; j++)
            analogWrite(STAR_PINS[i][j], starValues[i][j]);
}

void setAllStars(uint8_t value)
{
    for (int i = 0; i < NUM_STAR_MAIN; i++)
        for (int j = 0; j < NUM_STAR_SUB; j++)
            setStarValue(i, j, value);
}





// ------------------------- Driver code ---------------------------------------

// To allow non blocking animations / effects, don't use delay().
// A call to a `playEffect` function is just to set a specific color 
// at that current time.
// Use `tick` as a state for time elapsed, make sure to update it every loop.

#define TICK_MS 50
int tick = 0;

void setup()
{
    initStrips();
}

void loop()
{
    int start = millis();

    playSteadyState();
    showStrips();

    while (millis() - start < TICK_MS) delay(1);
    tick++;
}





// --------------------- Implementation of rainbow cycle ----------------------

// Num of leds to complete a rainbow cycle
#define BASE_RAINBOW_PERIOD 8
#define CITY_RAINBOW_PERIOD 8

// Length of ticks to complete a full cycle
#define BASE_DURATION 16
#define CITY_DURATION 16

void playSteadyState()
{
    for (int i = 0; i < NUM_OF_BASE; i++)
    {
        for (int j = 0; j < BASE_NUM_PIXELS; j++)
        {
            baseStrips[i].setPixelColor(j,
                wheel(i * 256 / BASE_RAINBOW_PERIOD + tick * 256 / BASE_DURATION));
        }
    }
    for (int i = 0; i < NUM_OF_CITY; i++)
    {
        for (int j = 0; j < CITY_NUM_PIXELS; j++)
        {
            cityStrips[i].setPixelColor(j,
                wheel(i * 256 / CITY_RAINBOW_PERIOD + tick * 256 / CITY_DURATION));
        }
    }
}

uint32_t wheel(uint8_t pos) {
    if (pos < 85)
    {
        return Adafruit_NeoPixel::Color(255 - pos * 3, pos * 3, 0);
    }
    else if (pos < 170)
    {
        pos -= 85;
        return Adafruit_NeoPixel::Color(0, 255 - pos * 3, pos * 3);
    }
    else
    {
        pos -= 170;
        return Adafruit_NeoPixel::Color(pos * 3, 0, 255 - pos * 3);
    }
}