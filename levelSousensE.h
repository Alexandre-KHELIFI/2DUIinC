#ifndef LEVELSOUSENSE_H_INCLUDED
#define LEVELSOUSENSE_H_INCLUDED

#include<SDL.h>

int state;
int combo;

void init_lvlSousensE(void);
void redirect_lvlSousensE(int, int*);
void destroy_lvlSousensE(void);
void update_lvlSousensE(int*, SDL_Event);
void draw_lvlSousensE(void);

#endif // LEVELSOUSENSE_H_INCLUDED
