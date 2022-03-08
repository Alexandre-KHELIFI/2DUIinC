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
#include "submenu.h"

void init_demo(void) {

	nbButtons = 0;int b=1;
	nbLmHitboxes = 0;int lm = 2;
	nbLfHitboxes = 0;int lf = 3; //quick fix for tests
	nbArrows = 0;
	bHitboxes = (Hitbox *) realloc(bHitboxes,b * sizeof(Hitbox));
	bTextures = (ButtonTexture *) realloc(bTextures,b * sizeof(ButtonTexture));
	lmHitboxes = (Hitbox *) realloc(lmHitboxes,lm * sizeof(Hitbox));
    lfHitboxes = (Hitbox *) realloc(lfHitboxes,lf * sizeof(Hitbox));
    linkIndexes = (int**)realloc (linkIndexes,lf*lm * sizeof(int*));
    for (int j=0;j<lf;j++) {
        linkIndexes[j] = malloc(lm * sizeof(int));
    }
    lmCounts = (int*)realloc(lmCounts, lm * sizeof(int));
    lTextures = (Texture *) realloc(lTextures,(lm+lf) * sizeof(Texture));
    aTextures = (Arrow *) realloc(aTextures,lf*lm * sizeof(Arrow));
	SDL_Color color = {0, 0, 0};

	//initialize "textbox"
	//initialize buttons
	create_button(0,S_WIDTH/2,3*S_HEIGHT/4,150,40,color,font,"Quit",textureIdle);
	//initialize links
    create_linkM(50,50);
    create_linkM(100,50);
    create_linkF(400,120);
    create_linkF(200,400);
    create_linkF(600,400);
    for (int j =0;j<nbLfHitboxes;j++) {
        for (int i =0;i<nbLmHitboxes;i++) {printf("d ");
            linkIndexes[j][i]=-1;
        }
        printf("\n");
    }
    for (int i=0;i<(nbLfHitboxes*nbLmHitboxes);i++) {
        create_arrow();
    }
    for(int i =0;i<nbLmHitboxes;i++) {
        lmCounts[i]=0;
    }
}

void destroy_demo(void) {
	for (int i = 0; i < nbButtons; i++) {
		SDL_DestroyTexture(bTextures[i].textTexture.texture);
	}
	for (int i=0;i<nbLfHitboxes;i++) {
        free(linkIndexes[i]);
	}
}

void redirect_demo(int index, int* quit) {
	switch(index) {
		case 0:
			//init
			destroy_demo();
			init_menu();
			UIupdate = update_menu;
			UIdraw = draw_default;
			break;
	}
}

void update_demo(int* quit, SDL_Event e) {
	while(SDL_PollEvent(&e) != 0) {
		handle_mickey_mouse(quit,&clickHandlerState,&indexButton,e,&oldIndex,redirect_demo,destroy_demo);
		handle_links(&indexLinkM, &indexArrow, e);
	}
}

void draw_demo(void) {
    SDL_RenderClear(gRenderer);
	SDL_RenderCopy(gRenderer, background.texture, NULL, &background.rect);
	for (int i = 0; i < nbTextures; i++) {
		SDL_RenderCopy(gRenderer, vTextures[i].texture, NULL, &vTextures[i].rect);
	}
	for (int i = 0; i < nbButtons; i++) {
		SDL_RenderCopy(gRenderer, bTextures[i].buttonTexture.texture, NULL, &bTextures[i].buttonTexture.rect);
		SDL_RenderCopy(gRenderer, bTextures[i].textTexture.texture, NULL, &bTextures[i].textTexture.rect);
	}
	for (int i = 0; i < nbLfHitboxes+nbLmHitboxes; i++) {
		SDL_RenderCopy(gRenderer, lTextures[i].texture, NULL, &lTextures[i].rect);
	}
	for (int i = 0; i < nbLfHitboxes*nbLmHitboxes; i++) {
        if (aTextures[i].vis != 0) {
            SDL_RenderCopyEx(gRenderer, aTextures[i].texture.texture, NULL, &aTextures[i].texture.rect,aTextures[i].angle,&aTextures[i].src,SDL_FLIP_NONE);
        }
	}
	SDL_RenderPresent(gRenderer);
}
