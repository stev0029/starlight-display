#include <stdio.h>

int tick = 0;

#define DURATION 10

enum State { STEADY, RISE, FALL, TWINKLE };

void playSteady()
{
    printf("Playing steady, tick %d\n", tick);
}

void playTransition()
{
    printf("Playing transition, tick %d\n", tick);
}

void playTwinkle()
{
    printf("Playing twinkle, tick %d\n", tick);
}

int main()
{
    State state = State::STEADY;
    bool sensor = false;

    while (1)
    {
        int a;
        scanf("%d", &a);

        if (a == 0)
            sensor = false;
        else if (a == 1)
            sensor = true;

        if (state == State::STEADY && sensor)
        {
            state = State::RISE;
            tick = 0;
        }
        else if (state == State::RISE && !sensor)
        {
            state = State::FALL;
            tick--;
        }
        else if (state == State::RISE && tick >= DURATION)
        {
            state = State::TWINKLE;
            tick = 0;
        }
        else if (state == State::TWINKLE && !sensor)
        {
            state = State::FALL;
            tick = DURATION - 1;
        }
        else if (state == State::FALL && sensor)
        {
            state = State::RISE;
            tick++;
        }
        else if (state == State::FALL && tick < 0)
        {
            state = State::STEADY;
            tick = 0;
        }

        switch (state)
        {
            case STEADY: playSteady(); tick++; break;
            case RISE: playTransition(); tick++; break;
            case FALL: playTransition(); tick--; break;
            case TWINKLE: playTwinkle(); tick++; break;
        }
    }
}