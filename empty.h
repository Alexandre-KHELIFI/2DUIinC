#ifndef EMPTY_H_INCLUDED
#define EMPTY_H_INCLUDED

#include<SDL.h>

void init_empty(void);
void redirect_empty(int, int*);
void destroy_empty(void);
void update_empty(int*, SDL_Event);
void draw_empty(void);

#endif // EMPTY_H_INCLUDED
