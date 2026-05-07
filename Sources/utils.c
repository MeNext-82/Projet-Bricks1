#include "utils.h"

double random_double(double min, double max) {
    double scale = rand() / (double)RAND_MAX;
    return min + scale * (max - min);
}

/****************************/
/*+ Time counter functions +*/
/****************************/

int time_start;
int time_counter;
bool time_paused = false;

void init_time_counter(void) {
    time_counter = 0;
    time_paused = false;
    time_start = SDL_GetTicks();
}

void init_time_counter_start(long start) {
    time_counter = start * 1000;
    time_paused = false;
    time_start = SDL_GetTicks();
}

void pause_time_counter(void) {
    time_counter += SDL_GetTicks() - time_start;
    time_paused = true;
}
void resume_time_counter(void) {
    time_paused = false;
    time_start = SDL_GetTicks();
}
int get_time_counter(void) {
    if (time_paused) {
        return time_counter;
    }
    else {
        return time_counter + SDL_GetTicks() - time_start;
    }
}
