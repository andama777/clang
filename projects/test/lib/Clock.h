#include <stdlib.h>

typedef struct{
    float tick;
    float gameTime;
    int pastTimeIndex;
    float* pastTimes;
} Clock;

Clock create_clock();
void tick(Clock *clock);
float get_game_time(Clock *clock);