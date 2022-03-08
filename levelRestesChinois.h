#ifndef LEVELRESTESCHINOIS_H_INCLUDED
#define LEVELRESTESCHINOIS_H_INCLUDED

#include<SDL.h>

int state;
int combo;

void init_lvlRestesChinois(void);
void redirect_lvlRestesChinois(int, int*);
void destroy_lvlRestesChinois(void);
void update_lvlRestesChinois(int*, SDL_Event);
void draw_lvlRestesChinois(void);

#endif // LEVELRESTESCHINOIS_H_INCLUDED
