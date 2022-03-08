#ifndef LEVELINDICEUL_H_INCLUDED
#define LEVELINDICEUL_H_INCLUDED

#include<SDL.h>

int state;
int combo;

void init_lvlIndicEul(void);
void redirect_lvlIndicEul(int, int*);
void destroy_lvlIndicEul(void);
void update_lvlIndicEul(int*, SDL_Event);
void draw_lvlIndicEul(void);

#endif // LEVELINDICEUL_H_INCLUDED
