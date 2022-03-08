#ifndef LEVELBIJ1_H_INCLUDED
#define LEVELBIJ1_H_INCLUDED

#include<SDL.h>

void init_lvlBij1(void);
void redirect_lvlBij1(int, int*);
void destroy_lvlBij1(void);
void update_lvlBij1(int*, SDL_Event);
void draw_lvlBij1(void);

#endif // LEVELBIJ1_H_INCLUDED
