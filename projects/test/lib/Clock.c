#include "Clock.h"

Clock create_clock() {
    Clock clock;
    clock.tick = 0.01;
    clock.gameTime = 0;
    clock.pastTimeIndex = 0;
    clock.pastTimes = malloc(sizeof(int) * 10);
    return clock;
}

void tick(Clock *clock) {
    clock->gameTime += clock->tick;
}

float get_game_time(Clock *clock){
    tick(clock);
    return clock->gameTime;
}
