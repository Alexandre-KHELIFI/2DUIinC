#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<string.h>
#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "UIengine.h"
#include "globals.h"
#include "mainmenu.h"

void init_timermenu(void) {

	nbButtons = 0;int b=1;
	nbTextures = 0;int t=6;
	bHitboxes = (Hitbox *) realloc(bHitboxes,b * sizeof(Hitbox));
	bTextures = (ButtonTexture *) realloc(bTextures,b * sizeof(ButtonTexture));
	vTextures = (Texture *) realloc(vTextures,t * sizeof(Texture));
	SDL_Color color = {0, 0, 0};

	//initialize text
	char names[3][16];
	strcpy(names[0],"level 1:");
	strcpy(names[1],"level 2:");
	strcpy(names[2],"level 3:");
	int comptT = 0;int comptI =0;
	for (int j=0;j<(nbTimers+1)/2;j++) {
        for (int i=1;i<5 && comptT<nbTimers;i+=3) {
            create_text(comptI++,i * S_WIDTH/6,(j+1) * S_HEIGHT/9,color,font,names[comptT]);
            create_text(comptI++,(i+1) * S_WIDTH/6,(j+1) * S_HEIGHT/9,color,font,"00:00:00");
            comptT++;
        }
	}
	//initialize buttons
	create_button(0,S_WIDTH/2,7*S_HEIGHT/8,S_WIDTH/4,S_HEIGHT/15,color,font,"Quit",textureIdle);
	//initialize links
}

void destroy_timermenu(void) {
	for (int i = 0; i < nbTextures; i++) {
		SDL_DestroyTexture(vTextures[i].texture);
	}
	for (int i = 0; i < nbButtons; i++) {
		SDL_DestroyTexture(bTextures[i].textTexture.texture);
	}
}

void redirect_timermenu(int index, int* quit) {
	switch(index) {
		case 0:
			//init
			destroy_timermenu();
			init_menu();
			UIupdate = update_menu;
			break;
	}
}

void update_timermenu(int* quit, SDL_Event e) {
	write_timers(timers, font);
	while(SDL_PollEvent(&e) != 0) {
		handle_mickey_mouse(quit,&clickHandlerState,&indexButton,e,&oldIndex,redirect_timermenu,destroy_timermenu);
	}
}
