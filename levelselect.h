#ifndef LEVELSELECT_H_INCLUDED
#define LEVELSELECT_H_INCLUDED

#include<SDL.h>

void init_lvlselect(void);
void redirect_lvlselect(int, int*);
void destroy_lvlselect(void);
void update_lvlselect(int*, SDL_Event);

#endif // LEVELSELECT_H_INCLUDED
