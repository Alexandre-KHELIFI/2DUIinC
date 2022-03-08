#ifndef HOWTO_H_INCLUDED
#define HOWTO_H_INCLUDED

#include<SDL.h>

void init_howto(void);
void redirect_howto(int, int*);
void destroy_howto(void);
void update_howto(int*, SDL_Event);

#endif // HOWTO_H_INCLUDED
