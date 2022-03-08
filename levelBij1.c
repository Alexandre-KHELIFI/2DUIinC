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
#include "levelBij1.h"
#include "levelselect.h"

void handle_arrows(void);

void init_lvlBij1(void) {

	nbButtons = 0;int b=2;
	nbTextures = 0;int t=1;
	nbLmHitboxes = 0;int lm = 4;
	nbLfHitboxes = 0;int lf = 3;//2 min
	nbArrows = 0;

	//buttons
	bHitboxes = (Hitbox *) realloc(bHitboxes,b * sizeof(Hitbox));
	bTextures = (ButtonTexture *) realloc(bTextures,b * sizeof(ButtonTexture));
	//various textures
	vTextures = (Texture *) realloc(vTextures,t * sizeof(Texture));
	//links and arrows
	lmHitboxes = (Hitbox *) realloc(lmHitboxes,lm * sizeof(Hitbox));
    lfHitboxes = (Hitbox *) realloc(lfHitboxes,lf * sizeof(Hitbox));
    linkIndexes = (int**)realloc (linkIndexes,lf*lm * sizeof(int*));
    for (int j=0;j<lf;j++) {
        linkIndexes[j] = malloc(lm * sizeof(int));
    }
    lmCounts = (int*)realloc(lmCounts, lm * sizeof(int));
    lTextures = (Texture *) realloc(lTextures,(lm+lf) * sizeof(Texture));
    aTextures = (Arrow *) realloc(aTextures,lf*lm * sizeof(Arrow));

    //da color
    daColor.r = 0;daColor.g = 0;daColor.b = 0;daColor.a = 255;
	SDL_Color color = {0, 0, 0};

	//initialize various
	create_text(0,S_WIDTH/2,S_HEIGHT/6,color,bigFont," ");
	//initialize buttons
	create_button(0,S_WIDTH/2,4*S_HEIGHT/5,S_WIDTH/4,S_HEIGHT/15,color,font,"Quit",textureIdle);
	create_button(1,S_WIDTH-(S_HEIGHT/15/2),S_HEIGHT/30,S_HEIGHT/15,S_HEIGHT/15,color,font,"M",textureIdle);
    //initialize links and arrows (right order ms->fs)
	create_linkM(S_WIDTH/4,S_HEIGHT/3);
	create_linkM(S_WIDTH/4,S_HEIGHT/3+(S_HEIGHT/15+S_HEIGHT/40));
	create_linkM(S_WIDTH/4,S_HEIGHT/3+(S_HEIGHT/15+S_HEIGHT/40)*2);
	create_linkM(S_WIDTH/4,S_HEIGHT/3+(S_HEIGHT/15+S_HEIGHT/40)*3);
    create_linkF(3*S_WIDTH/4,S_HEIGHT/3);
    create_linkF(3*S_WIDTH/4,S_HEIGHT/3+(S_HEIGHT/15+S_HEIGHT/40));
    create_linkF(3*S_WIDTH/4,S_HEIGHT/3+(S_HEIGHT/15+S_HEIGHT/40)*2);
    for (int j =0;j<nbLfHitboxes;j++) {
        for (int i =0;i<nbLmHitboxes;i++) {
            linkIndexes[j][i]=-1;
        }
    }
    for (int i=0;i<(nbLfHitboxes*nbLmHitboxes);i++) {
        create_arrow();
    }
    for(int i =0;i<nbLmHitboxes;i++) {
        lmCounts[i]=0;
    }
}

void destroy_lvlBij1(void) {
	for (int i = 0; i < nbTextures; i++) {
		SDL_DestroyTexture(vTextures[i].texture);
	}
	for (int i = 0; i < nbButtons; i++) {
		SDL_DestroyTexture(bTextures[i].textTexture.texture);
	}
    for (int i=0;i<nbLfHitboxes;i++) {
        free(linkIndexes[i]);
	}
}

void redirect_lvlBij1(int index, int* quit) {
	switch(index) {
		case 0:
			//init
			destroy_lvlBij1();
			init_lvlselect();
			UIupdate = update_lvlselect;
			UIdraw = draw_default;
			break;
        case 1:
            if (mPause==0) {
                Mix_PauseMusic();
                mPause = 1;
            }
            else {
                Mix_ResumeMusic();
                mPause = 0;
            }
			break;
	}
}

void update_lvlBij1(int* quit, SDL_Event e) {
	while(SDL_PollEvent(&e) != 0) {
        handle_links(&indexLinkM, &indexArrow, e);
		handle_arrows();//see main for "name" global
		handle_mickey_mouse(quit,&clickHandlerState,&indexButton,e,&oldIndex,redirect_lvlBij1,destroy_lvlBij1);
	}
}

void handle_arrows(void) {
//impossible: linkM has 2 arrows, injective: no two linkM has same linkF, surjective: every linkF is linked
    int compt=0;
    for(int i=0;i<nbLmHitboxes;i++) {
        if (lmCounts[i]>1) {
            set_text(0,bigFont,"IMPOSSIBLE",daColor);
            return;
        }
        else if (lmCounts[i]) {
            compt++;
        }
    }
    if (!compt) {
        set_text(0,bigFont," ",daColor);
        return;
    }
    int same=0;int notInj=0;int notSurj=0;
    for(int j=0;j<nbLfHitboxes;j++) {
        for(int i=0;i<nbLmHitboxes;i++) {
            if (linkIndexes[j][i]!=-1) {
                same++;
            }
        }
        if (same>1) {
            notInj=1;
        }
        else if (same==0) {
            notSurj=1;
        }
        same=0;
    }
    if (!notSurj && !notInj) {
        set_text(0,bigFont,"BIJECTION",daColor);
    }
    else if (!notSurj) {
        set_text(0,bigFont,"SURJECTION",daColor);
    }
    else if (!notInj) {
        set_text(0,bigFont,"INJECTION",daColor);
    }
    else {
        set_text(0,bigFont," ",daColor);
    }
}


/**
*   You can use the draw_default if there is no link/arrow in the window.
*/
void draw_lvlBij1(void) {
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
