#ifndef LEVELBEZOUT_H_INCLUDED
#define LEVELBEZOUT_H_INCLUDED

#include<SDL.h>

int state;
int combo;

void init_lvlBezout(void);
void redirect_lvlBezout(int, int*);
void destroy_lvlBezout(void);
void update_lvlBezout(int*, SDL_Event);
void draw_lvlBezout(void);

#endif // LEVELBEZOUT_H_INCLUDED
