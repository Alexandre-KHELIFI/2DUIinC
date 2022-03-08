#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include "UIengine.h"
#include "globals.h"
#include "mainmenu.h"
#include "howto.h"
#include "timermenu.h"
#include "levelselect.h"

void init_menu(void) {

	nbButtons = 0;int b=5;
	nbTextures = 0;int t=1;
	bHitboxes = (Hitbox *) realloc(bHitboxes,b * sizeof(Hitbox));
	bTextures = (ButtonTexture *) realloc(bTextures,b * sizeof(ButtonTexture));
	vTextures = (Texture *) realloc(vTextures,t * sizeof(Texture));
	SDL_Color color = {0, 0, 0};

	create_text(0,S_WIDTH/2,S_HEIGHT/3,color,bigFont,"DA GAME");
	//create_various_texture(1,S_WIDTH/2,S_HEIGHT/2,S_WIDTH/10,S_HEIGHT/10,"images/buttons/idle.png");
	//initialize "textbox"
	//initialize buttons
	create_button(0,S_WIDTH/4,2*S_HEIGHT/3,S_WIDTH/6,S_HEIGHT/15,color,font,"Start",textureIdle);
	create_button(1,3*S_WIDTH/4,2*S_HEIGHT/3,S_WIDTH/6,S_HEIGHT/15,color,font,"Quit",textureIdle);
	create_button(2,S_WIDTH-(S_HEIGHT/15/2),S_HEIGHT/30,S_HEIGHT/15,S_HEIGHT/15,color,font,"M",textureIdle);
	create_button(3,S_WIDTH/2,2*S_HEIGHT/3,S_WIDTH/6,S_HEIGHT/15,color,font,"Levels",textureIdle);
}

void destroy_menu(void) {
	for (int i = 0; i < nbTextures; i++) {
		SDL_DestroyTexture(vTextures[i].texture);
	}
	for (int i = 0; i < nbButtons; i++) {
		SDL_DestroyTexture(bTextures[i].textTexture.texture);
	}

}

void redirect_menu(int index, int* quit) {
	switch(index) {
		case 0:
			//init
			destroy_menu();
			init_howto();
			UIupdate = update_howto;
			UIdraw = draw_default;
			break;
		case 1:
			destroy_menu();
			*quit = 1;
			break;
        case 2:
            if (mPause==0) {
                Mix_PauseMusic();
                mPause = 1;
            }
            else {
                Mix_ResumeMusic();
                mPause = 0;
            }
			break;
        case 3:
			destroy_menu();
			init_lvlselect();
			UIupdate = update_lvlselect;
			UIdraw = draw_default;
			break;
	}
}

void update_menu(int* quit, SDL_Event e) {
	while(SDL_PollEvent(&e) != 0) {
		handle_mickey_mouse(quit,&clickHandlerState,&indexButton,e,&oldIndex,redirect_menu,destroy_menu);
	}
}
