#ifndef LEVELNBBIJSURA_H_INCLUDED
#define LEVELNBBIJSURA_H_INCLUDED

#include<SDL.h>

int state;
int combo;

void init_lvlNbBijsurA(void);
void redirect_lvlNbBijsurA(int, int*);
void destroy_lvlNbBijsurA(void);
void update_lvlNbBijsurA(int*, SDL_Event);
void draw_lvlNbBijsurA(void);

#endif // LEVELNBBIJSURA_H_INCLUDED
