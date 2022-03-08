#ifndef LEVELTEMPLATE_H_INCLUDED
#define LEVELTEMPLATE_H_INCLUDED

#include<SDL.h>

int state;
int combo;

void init_lvltemp(void);
void redirect_lvltemp(int, int*);
void destroy_lvltemp(void);
void update_lvltemp(int*, SDL_Event);
void draw_lvltemp(void);

#endif // LEVELTEMPLATE_H_INCLUDED
