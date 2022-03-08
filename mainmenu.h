#ifndef MAINMENU_H_INCLUDED
#define MAINMENU_H_INCLUDED

#include<SDL.h>

int mPause;

void init_menu(void);
void redirect_menu(int, int*);
void destroy_menu(void);
void update_menu(int* , SDL_Event);

#endif // MAINMENU_H_INCLUDED
