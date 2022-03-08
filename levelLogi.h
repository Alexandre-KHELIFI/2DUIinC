#ifndef LEVELLOGI_H_INCLUDED
#define LEVELLOGI_H_INCLUDED

#include<SDL.h>

int state;
int combo;

void init_lvlLogi(void);
void redirect_lvlLogi(int, int*);
void destroy_lvlLogi(void);
void update_lvlLogi(int*, SDL_Event);
void draw_lvlLogi(void);

#endif // LEVELLOGI_H_INCLUDED
