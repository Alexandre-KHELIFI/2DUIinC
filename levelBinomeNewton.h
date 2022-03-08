#ifndef LEVELBINOMENEWTON_H_INCLUDED
#define LEVELBINOMENEWTON_H_INCLUDED

#include<SDL.h>

int state;
int combo;

void init_lvlBinomeNewton(void);
void redirect_lvlBinomeNewton(int, int*);
void destroy_lvlBinomeNewton(void);
void update_lvlBinomeNewton(int*, SDL_Event);
void draw_lvlBinomeNewton(void);

#endif // LEVELBINOMENEWTON_H_INCLUDED
