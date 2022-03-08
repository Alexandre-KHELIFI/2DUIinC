#ifndef LEVELCOEFFBINOM_H_INCLUDED
#define LEVELCOEFFBINOM_H_INCLUDED

#include<SDL.h>

int state;
int combo;

void init_lvlCoeffBinom(void);
void redirect_lvlCoeffBinom(int, int*);
void destroy_lvlCoeffBinom(void);
void update_lvlCoeffBinom(int*, SDL_Event);
void draw_lvlCoeffBinom(void);

#endif // LEVELCOEFFBINOM_H_INCLUDED
