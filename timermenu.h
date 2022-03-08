#ifndef TIMERMENU_H_INCLUDED
#define TIMERMENU_H_INCLUDED

#include<SDL.h>

void init_timermenu(void);
void redirect_timermenu(int, int*);
void destroy_timermenu(void);
void update_timermenu(int*, SDL_Event);

#endif // TIMERMENU_H_INCLUDED
