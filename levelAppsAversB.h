#ifndef LEVELAPPSAVERSB_H_INCLUDED
#define LEVELAPPSAVERSB_H_INCLUDED

#include<SDL.h>

int state;
int combo;

void init_lvlAppsAversB(void);
void redirect_lvlAppsAversB(int, int*);
void destroy_lvlAppsAversB(void);
void update_lvlAppsAversB(int*, SDL_Event);
void draw_lvlAppsAversB(void);

#endif // LEVELAPPSAVERSB_H_INCLUDED
