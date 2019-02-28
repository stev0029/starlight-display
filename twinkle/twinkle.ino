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
const uint8_t STAR_PINS[3][3] = {
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

    playTwinkleStar();
    showStrips();
    showStars();

    while (millis() - start < TICK_MS) delay(1);
    tick++;
}





// ---------------------- Twinkle Star Implementation -------------------------

#define LOWER_VALUE 128
#define UPPER_VALUE 255
#define DECREASE_RATE 1
#define TWINKLE_INTERVAL 2

void playTwinkleStar()
{
    if (tick == 0) setAllStars(LOWER_VALUE);

    // Dim every star each tick
    for (int i = 0; i < NUM_STAR_MAIN; i++)
        for (int j = 0; j < NUM_STAR_SUB; j++)
        {
            setStarValue(i, j, getStarValue(i, j) - DECREASE_RATE);
            if (getStarValue(i, j) < LOWER_VALUE)
                setStarValue(i, j, LOWER_VALUE);
        }
    
    // Randomly determine which 'star' to twinkle
    if (tick % TWINKLE_INTERVAL == random(TWINKLE_INTERVAL))
    {
        setStarValue(random(NUM_STAR_MAIN), random(NUM_STAR_SUB), UPPER_VALUE);
    }
}