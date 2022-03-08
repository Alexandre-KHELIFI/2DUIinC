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
#include "howto.h"
#include "mainmenu.h"

void init_howto(void) {

	nbButtons = 0;int b=2;
	nbTextures = 0;int t=19;

	//buttons
	bHitboxes = (Hitbox *) realloc(bHitboxes,b * sizeof(Hitbox));
	bTextures = (ButtonTexture *) realloc(bTextures,b * sizeof(ButtonTexture));
	//various textures
	vTextures = (Texture *) realloc(vTextures,t * sizeof(Texture));
	//links and arrows
    //da color
	SDL_Color color = {0, 0, 0};

	//initialize various
	create_text(0,S_WIDTH/2,S_HEIGHT/15,color,font,"INSTRUCTIONS");
	create_text(1,S_WIDTH/2,2*S_HEIGHT/15,color,font,"HOW TO");
	create_text(2,S_WIDTH/2,3*S_HEIGHT/17+17,color,font,"Il  faut  faire  tous  les  exercices  dans  l'ordre  'A'  et  'B'.");
	create_text(3,S_WIDTH/2,3*S_HEIGHT/17+17*2,color,font,"Les  exercices  'A'  vous  guident  sur  comment  réussir  les  exercices  'B'.");
	create_text(4,S_WIDTH/2,3*S_HEIGHT/17+17*3,color,font,"Pour  l'exercice  1,  il  faut  faire  exercice1  'A'  puis  exercice1  'B'.");
	create_text(5,S_WIDTH/2,3*S_HEIGHT/17+17*4,color,font,"Une  fois  réussit,  l'exercice  'B'  lance  un  compteur,  et  il" );
	create_text(6,S_WIDTH/2,3*S_HEIGHT/17+17*5,color,font,"faudra  le  refaire  30  à  60  minutes  plus  tard.  L'exercice  sera  considéré");
	create_text(7,S_WIDTH/2,3*S_HEIGHT/17+17*6,color,font,"comme  acquis,  mais  refaite  le  une  fois  par  jour  pendant  une  semaine,");
	create_text(8,S_WIDTH/2,3*S_HEIGHT/17+17*7,color,font,"puis  deux  fois  par  semaine  pour  l'apprendre  correctement.");
	create_text(9,S_WIDTH/2,3*S_HEIGHT/17+17*8+10,color,font,"Une  fois  un  exercice  'A'  réussi,  il  ne  devrait  pas  être  refait: c'est tricher.");
	create_text(10,S_WIDTH/2,8*S_HEIGHT/17+17,color,font,"You  need  to  do  every  exercise  in  'A'  'B'  order.");
	create_text(11,S_WIDTH/2,8*S_HEIGHT/17+17*2,color,font,"'A'  parts  teach  you  how  to  complete  'B'  parts.");
	create_text(12,S_WIDTH/2,8*S_HEIGHT/17+17*3,color,font,"and  then  exercise1  'B'.");
	create_text(13,S_WIDTH/2,8*S_HEIGHT/17+17*4,color,font,"Once  done,  the  completed  'B'  part  will  start  a  timer,");
	create_text(14,S_WIDTH/2,8*S_HEIGHT/17+17*5,color,font,"and  you  will  have  to  do  the  'B'  part  again  in");
	create_text(15,S_WIDTH/2,8*S_HEIGHT/17+17*6,color,font,"30  to  60  minutes.  The  exercise  will  be  considered");
	create_text(16,S_WIDTH/2,8*S_HEIGHT/17+17*7,color,font,"mastered,  but  you  should  do  it  again  once  every  day");
	create_text(17,S_WIDTH/2,8*S_HEIGHT/17+17*8,color,font,"for  some  time,  then  once  every  week.");
	create_text(18,S_WIDTH/2,8*S_HEIGHT/17+17*10,color,font,"'A'  parts  should  be  done  only  once,  only  'B'  parts  should  be  repeated, or else it's cheating.");
	//initialize buttons
	create_button(0,S_WIDTH/2,4*S_HEIGHT/5+20,S_WIDTH/4,S_HEIGHT/15,color,font,"Quit",textureIdle);
	create_button(1,S_WIDTH-(S_HEIGHT/15/2),S_HEIGHT/30,S_HEIGHT/15,S_HEIGHT/15,color,font,"M",textureIdle);
    //initialize links and arrows (right order ms->fs)
}

void destroy_howto(void) {
	for (int i = 0; i < nbTextures; i++) {
		SDL_DestroyTexture(vTextures[i].texture);
	}
	for (int i = 0; i < nbButtons; i++) {
		SDL_DestroyTexture(bTextures[i].textTexture.texture);
	}
}

void redirect_howto(int index, int* quit) {
	switch(index) {
		case 0:
			//init
			destroy_howto();
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
	}
}

void update_howto(int* quit, SDL_Event e) {
	while(SDL_PollEvent(&e) != 0) {
		handle_mickey_mouse(quit,&clickHandlerState,&indexButton,e,&oldIndex,redirect_howto,destroy_howto);
	}
}
