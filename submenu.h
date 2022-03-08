#ifndef SUBMENU_H_INCLUDED
#define SUBMENU_H_INCLUDED

#include<SDL.h>

void init_demo(void);
void redirect_demo(int, int*);
void destroy_demo(void);
void update_demo(int*, SDL_Event);
void draw_demo(void);

#endif // SUBMENU_H_INCLUDED
