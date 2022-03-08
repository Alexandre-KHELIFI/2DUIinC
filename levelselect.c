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
#include "levelselect.h"
#include "levelAppsAversB.h"
#include "levelBezout.h"
#include "levelBij1.h"
#include "levelBinomeNewton.h"
#include "levelCoeffBinom.h"
#include "levelFermat.h"
#include "levelIndicEul.h"
#include "levelLogi.h"
#include "levelNbBijsurA.h"
#include "levelRestesChinois.h"
#include "levelSousensE.h"
#include "leveltemplate.h"

#include "empty.h"


void init_lvlselect(void) {

	nbButtons = 0;int b=23;
	nbTextures = 0;int t=21;
	bHitboxes = (Hitbox *) realloc(bHitboxes,b * sizeof(Hitbox));
	bTextures = (ButtonTexture *) realloc(bTextures,b * sizeof(ButtonTexture));
	vTextures = (Texture *) realloc(vTextures,t * sizeof(Texture));
	SDL_Color color = {0, 0, 0};

	//initialize buttons
	create_button(0,S_WIDTH/2,4*S_HEIGHT/5,S_WIDTH/4,S_HEIGHT/15,color,font,"Quit",textureIdle);
	create_button(1,S_WIDTH-(S_HEIGHT/15/2),S_HEIGHT/30,S_HEIGHT/15,S_HEIGHT/15,color,font,"M",textureIdle);
	create_text(0,1*S_WIDTH/8,1*S_HEIGHT/9-3,color,font,"Coefficient binomiaux  :");
	create_text(1,1*S_WIDTH/8,1*S_HEIGHT/9+9,color,font,"00:00:00");
	create_button(2,3*S_WIDTH/10,1*S_HEIGHT/9,S_WIDTH/15,S_HEIGHT/15,color,font,"A",textureIdle);
	create_button(3,4*S_WIDTH/10,1*S_HEIGHT/9,S_WIDTH/15,S_HEIGHT/15,color,font,"B",textureIdle);

	create_text(2,5*S_WIDTH/8,1*S_HEIGHT/9-3,color,font,"Binome de Newton  :");
	create_text(3,5*S_WIDTH/8,1*S_HEIGHT/9+9,color,font,"00:00:00");
	create_button(4,8*S_WIDTH/10,1*S_HEIGHT/9,S_WIDTH/15,S_HEIGHT/15,color,font,"A",textureIdle);
	create_button(5,9*S_WIDTH/10,1*S_HEIGHT/9,S_WIDTH/15,S_HEIGHT/15,color,font,"B",textureIdle);

	create_text(4,1*S_WIDTH/8,2*S_HEIGHT/9-3,color,font,"Nb Apps A vers B  :");
	create_text(5,1*S_WIDTH/8,2*S_HEIGHT/9+9,color,font,"00:00:00");
	create_button(6,3*S_WIDTH/10,2*S_HEIGHT/9,S_WIDTH/15,S_HEIGHT/15,color,font,"A",textureIdle);
	create_button(7,4*S_WIDTH/10,2*S_HEIGHT/9,S_WIDTH/15,S_HEIGHT/15,color,font,"B",textureIdle);

	create_text(6,5*S_WIDTH/8,2*S_HEIGHT/9-3,color,font,"Nb parties d'un ensemble  :");
	create_text(7,5*S_WIDTH/8,2*S_HEIGHT/9+9,color,font,"00:00:00");
	create_button(8,8*S_WIDTH/10,2*S_HEIGHT/9,S_WIDTH/15,S_HEIGHT/15,color,font,"A",textureIdle);
	create_button(9,9*S_WIDTH/10,2*S_HEIGHT/9,S_WIDTH/15,S_HEIGHT/15,color,font,"B",textureIdle);

	create_text(8,1*S_WIDTH/8,3*S_HEIGHT/9-3,color,font,"Nb bijections vers A  :");
	create_text(9,1*S_WIDTH/8,3*S_HEIGHT/9+9,color,font,"00:00:00");
	create_button(10,3*S_WIDTH/10,3*S_HEIGHT/9,S_WIDTH/15,S_HEIGHT/15,color,font,"A",textureIdle);
	create_button(11,4*S_WIDTH/10,3*S_HEIGHT/9,S_WIDTH/15,S_HEIGHT/15,color,font,"B",textureIdle);

	create_text(10,1*S_WIDTH/8,4*S_HEIGHT/9-3,color,font,"Bezout  :");
	create_text(11,1*S_WIDTH/8,4*S_HEIGHT/9+9,color,font,"00:00:00");
	create_button(12,3*S_WIDTH/10,4*S_HEIGHT/9,S_WIDTH/15,S_HEIGHT/15,color,font,"A",textureIdle);
	create_button(13,4*S_WIDTH/10,4*S_HEIGHT/9,S_WIDTH/15,S_HEIGHT/15,color,font,"B",textureIdle);

	create_text(12,5*S_WIDTH/8,4*S_HEIGHT/9-3,color,font,"Indicateur  d'Euler  :");
	create_text(13,5*S_WIDTH/8,4*S_HEIGHT/9+9,color,font,"00:00:00");
	create_button(14,8*S_WIDTH/10,4*S_HEIGHT/9,S_WIDTH/15,S_HEIGHT/15,color,font,"A",textureIdle);
	create_button(15,9*S_WIDTH/10,4*S_HEIGHT/9,S_WIDTH/15,S_HEIGHT/15,color,font,"B",textureIdle);

	create_text(14,1*S_WIDTH/8,5*S_HEIGHT/9-3,color,font,"Fermat  :");
	create_text(15,1*S_WIDTH/8,5*S_HEIGHT/9+9,color,font,"00:00:00");
	create_button(16,3*S_WIDTH/10,5*S_HEIGHT/9,S_WIDTH/15,S_HEIGHT/15,color,font,"A",textureIdle);
	create_button(17,4*S_WIDTH/10,5*S_HEIGHT/9,S_WIDTH/15,S_HEIGHT/15,color,font,"B",textureIdle);

	create_text(16,5*S_WIDTH/8,5*S_HEIGHT/9-3,color,font,"Logique  :");
	create_text(17,5*S_WIDTH/8,5*S_HEIGHT/9+9,color,font,"00:00:00");
	create_button(18,8*S_WIDTH/10,5*S_HEIGHT/9,S_WIDTH/15,S_HEIGHT/15,color,font,"A",textureIdle);
	create_button(19,9*S_WIDTH/10,5*S_HEIGHT/9,S_WIDTH/15,S_HEIGHT/15,color,font,"B",textureIdle);

	create_text(18,1*S_WIDTH/8,6*S_HEIGHT/9-3,color,font,"Restes  Chinois  :");
	create_text(19,1*S_WIDTH/8,6*S_HEIGHT/9+9,color,font,"00:00:00");
	create_button(20,3*S_WIDTH/10,6*S_HEIGHT/9,S_WIDTH/15,S_HEIGHT/15,color,font,"A",textureIdle);
	create_button(21,4*S_WIDTH/10,6*S_HEIGHT/9,S_WIDTH/15,S_HEIGHT/15,color,font,"B",textureIdle);

	create_text(20,5*S_WIDTH/8,6*S_HEIGHT/9,color,font,"Injection Surjection  :");
	create_button(22,8*S_WIDTH/10,6*S_HEIGHT/9,S_WIDTH/15,S_HEIGHT/15,color,font,"A",textureIdle);
}

void destroy_lvlselect(void) {
	for (int i = 0; i < nbTextures; i++) {
		SDL_DestroyTexture(vTextures[i].texture);
	}
	for (int i = 0; i < nbButtons; i++) {
		SDL_DestroyTexture(bTextures[i].textTexture.texture);
	}

}

void redirect_lvlselect(int index, int* quit) {
	switch(index) {
		case 0:
			//init
			destroy_lvlselect();
			init_menu();
			UIupdate = update_menu;
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
        case 2:
			//init
			destroy_lvlselect();
            exoMode = 0;
			init_lvlCoeffBinom();
			UIupdate = update_lvlCoeffBinom;
			UIdraw = draw_lvlCoeffBinom;
			break;
        case 3:
			//init
			destroy_lvlselect();
			exoMode = 1;
			init_lvlCoeffBinom();
			UIupdate = update_lvlCoeffBinom;
			UIdraw = draw_lvlCoeffBinom;
			break;
        case 4:
			//init
			destroy_lvlselect();
            exoMode = 0;
			init_lvlBinomeNewton();
			UIupdate = update_lvlBinomeNewton;
			UIdraw = draw_lvlBinomeNewton;
			break;
        case 5:
			//init
			destroy_lvlselect();
			exoMode = 1;
			init_lvlBinomeNewton();
			UIupdate = update_lvlBinomeNewton;
			UIdraw = draw_lvlBinomeNewton;
			break;
        case 6:
			//init
			destroy_lvlselect();
            exoMode = 0;
			init_lvlAppsAversB();
			UIupdate = update_lvlAppsAversB;
			UIdraw = draw_lvlAppsAversB;
			break;
        case 7:
			//init
			destroy_lvlselect();
			exoMode = 1;
			init_lvlAppsAversB();
			UIupdate = update_lvlAppsAversB;
			UIdraw = draw_lvlAppsAversB;
			break;
        case 8:
			//init
			destroy_lvlselect();
            exoMode = 0;
			init_lvlSousensE();
			UIupdate = update_lvlSousensE;
			UIdraw = draw_lvlSousensE;
			break;
        case 9:
			//init
			destroy_lvlselect();
			exoMode = 1;
			init_lvlSousensE();
			UIupdate = update_lvlSousensE;
			UIdraw = draw_lvlSousensE;
			break;
        case 10:
			//init
			destroy_lvlselect();
            exoMode = 0;
			init_lvlNbBijsurA();
			UIupdate = update_lvlNbBijsurA;
			UIdraw = draw_lvlNbBijsurA;
			break;
        case 11:
			//init
			destroy_lvlselect();
			exoMode = 1;
			init_lvlNbBijsurA();
			UIupdate = update_lvlNbBijsurA;
			UIdraw = draw_lvlNbBijsurA;
			break;
        case 12:
			//init
			destroy_lvlselect();
            exoMode = 0;
			init_lvlBezout();
			UIupdate = update_lvlBezout;
			UIdraw = draw_lvlBezout;
			break;
        case 13:
			//init
			destroy_lvlselect();
			exoMode = 1;
			init_lvlBezout();
			UIupdate = update_lvlBezout;
			UIdraw = draw_lvlBezout;
			break;
        case 14:
			//init
			destroy_lvlselect();
            exoMode = 0;
			init_lvlIndicEul();
			UIupdate = update_lvlIndicEul;
			UIdraw = draw_lvlIndicEul;
			break;
        case 15:
			//init
			destroy_lvlselect();
			exoMode = 1;
			init_lvlIndicEul();
			UIupdate = update_lvlIndicEul;
			UIdraw = draw_lvlIndicEul;
			break;
        case 16:
			//init
			destroy_lvlselect();
            exoMode = 0;
			init_lvlFermat();
			UIupdate = update_lvlFermat;
			UIdraw = draw_lvlFermat;
			break;
        case 17:
			//init
			destroy_lvlselect();
			exoMode = 1;
			init_lvlFermat();
			UIupdate = update_lvlFermat;
			UIdraw = draw_lvlFermat;
			break;
        case 18:
			//init
			destroy_lvlselect();
            exoMode = 0;
			init_lvlLogi();
			UIupdate = update_lvlLogi;
			UIdraw = draw_lvlLogi;
			break;
        case 19:
			//init
			destroy_lvlselect();
			exoMode = 1;
			init_lvlLogi();
			UIupdate = update_lvlLogi;
			UIdraw = draw_lvlLogi;
			break;
        case 20:
			//init
			destroy_lvlselect();
            exoMode = 0;
			init_lvlRestesChinois();
			UIupdate = update_lvlRestesChinois;
			UIdraw = draw_lvlRestesChinois;
			break;
        case 21:
			//init
			destroy_lvlselect();
			exoMode = 1;
			init_lvlRestesChinois();
			UIupdate = update_lvlRestesChinois;
			UIdraw = draw_lvlRestesChinois;
			break;
        case 22:
			//init
			destroy_lvlselect();
			exoMode = 0;
			init_lvlBij1();
			UIupdate = update_lvlBij1;
			UIdraw = draw_lvlBij1;
			break;
        /*case 6:
			//init
			destroy_lvlselect();
			exoMode = 0;
			init_lvlBij1();
			UIupdate = update_lvlBij1;
			UIdraw = draw_lvlBij1;
			break;
        case 5:
			//init
			destroy_lvlselect();
			init_empty();
			UIupdate = update_empty;
			UIdraw = draw_empty;
			break;
        case 4:
			//init
			destroy_lvlselect();
			exoMode = 0;
			init_lvlBinomeNewton();
			UIupdate = update_lvlBinomeNewton;
			UIdraw = draw_lvlBinomeNewton;
			break;*/
	}
}

void update_lvlselect(int* quit, SDL_Event e) {
    write_timers(timers, font);
	while(SDL_PollEvent(&e) != 0) {
		handle_mickey_mouse(quit,&clickHandlerState,&indexButton,e,&oldIndex,redirect_lvlselect,destroy_lvlselect);
	}
}
