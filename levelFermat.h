#ifndef LEVELFERMAT_H_INCLUDED
#define LEVELFERMAT_H_INCLUDED

#include<SDL.h>

int state;
int combo;

void init_lvlFermat(void);
void redirect_lvlFermat(int, int*);
void destroy_lvlFermat(void);
void update_lvlFermat(int*, SDL_Event);
void draw_lvlFermat(void);

#endif // LEVELFERMAT_H_INCLUDED
