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
#include "levelselect.h"
#include "leveltemplate.h"

void handle_keyboard(SDL_Event e);

void init_lvltemp(void) {

	nbButtons = 0;int b=2;
	nbTextures = 0;int t=4;
	nbBlanks = 0;int bl=3;
	bHitboxes = (Hitbox *) realloc(bHitboxes,b * sizeof(Hitbox));
	bTextures = (ButtonTexture *) realloc(bTextures,b * sizeof(ButtonTexture));
	vTextures = (Texture *) realloc(vTextures,t * sizeof(Texture));
	blanks = (Blank *) realloc(blanks,bl * sizeof(Blank));

	daColor.r = 0;daColor.g = 0;daColor.b = 0;daColor.a = 255;
	SDL_Color color = {0,0,0};

	//initialize buttons
	create_button(0,S_WIDTH/2,4*S_HEIGHT/5,S_WIDTH/4,S_HEIGHT/15,color,font,"Quit",textureIdle);
	create_button(1,S_WIDTH-(S_HEIGHT/15/2),S_HEIGHT/30,S_HEIGHT/15,S_HEIGHT/15,color,font,"M",textureIdle);
	//initialize various textures/texts
	create_text(0,S_WIDTH/2,S_HEIGHT/8,color,font,"Coefficient Binomial");
    create_various_texture(1,S_WIDTH/2,3*S_HEIGHT/10,S_WIDTH/3,S_HEIGHT/9,"images/formulas/coeffbinom.JPG");
    create_text(2,S_WIDTH/2,6*S_HEIGHT/10,color,bigFont,"ENTER");
    create_text(3,S_WIDTH/2,6*S_HEIGHT/10,color,arrowFont," ");
	//initialize blanks (last to first 0->n)
	create_blank(0,S_WIDTH/2-S_WIDTH/8, 3*S_HEIGHT/10, S_WIDTH/3/4, S_HEIGHT/9);
	create_blank(1,S_WIDTH/2+S_WIDTH/17, 3*S_HEIGHT/10-S_HEIGHT/9/3, S_WIDTH/3/4*2, S_HEIGHT/9/2);
	create_blank(2,S_WIDTH/2+S_WIDTH/17, 3*S_HEIGHT/10+S_HEIGHT/9/4, S_WIDTH/3/5*3, S_HEIGHT/9/2);

	instructions = (char **) realloc(instructions, 8*sizeof(char*));
	char* instrs[8] = {"n","C","k","D","n!","C","k!(n-k)!","D"};
	if (exoMode==1) {
        for (int i=0;i<8;i++) {
            instrs[i]=" ";
        }
	}
	for (int j=0;j<8;j++) {
        instructions[j] = (char *) malloc(8 * sizeof(char));
        strcpy(instructions[j],instrs[j]);
    }
    state=0;combo=0;
    indexTimer=0;
}

void destroy_lvltemp(void) {
	for (int i = 0; i < nbTextures; i++) {
		SDL_DestroyTexture(vTextures[i].texture);
	}
	for (int i = 0; i < nbButtons; i++) {
		SDL_DestroyTexture(bTextures[i].textTexture.texture);
	}
	for (int j=0;j<8;j++) {
        free(instructions[j]);
    }
}

void redirect_lvltemp(int index, int* quit) {
	switch(index) {
		case 0:
			//init
			destroy_lvltemp();
			if (mPause) {
                Mix_PlayMusic(gMusic, -1);
                Mix_PauseMusic();
			}
			else {
                Mix_PlayMusic(gMusic, -1);
			}
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

void update_lvltemp(int* quit, SDL_Event e) {
	while(SDL_PollEvent(&e) != 0) {
        handle_keyboard(e);
		handle_mickey_mouse(quit,&clickHandlerState,&indexButton,e,&oldIndex,redirect_lvltemp,destroy_lvltemp);
	}
}

void handle_keyboard(SDL_Event e) {
    switch(e.type) {
		case SDL_KEYDOWN:
			if (e.key.keysym.sym == SDLK_UP) {
                if ((state==1 && combo == 1) || (state==3 && combo == 2)) {
                    set_instructions(2,3,bigFont,arrowFont, instructions[state*2], instructions[state*2+1], daColor);
                    blanks[state-2].vis = 0;
                    state++;
                    combo=0;
                    Mix_PlayChannel(-1, unClick, 0);
                }
                else {
                    combo=0;
                }
			}
			else if (e.key.keysym.sym == SDLK_DOWN) {
                if ((state==2 && combo == 1)) {
                    set_instructions(2,3,bigFont,arrowFont, instructions[state*2], instructions[state*2+1], daColor);
                    combo=0;
                    Mix_PlayChannel(-1, unClick, 0);
                    if (state>1) {
                        blanks[state-2].vis = 0;
                    }
                    state++;
                }
                else if (state==4 && combo == 8) {
                    blanks[state-2].vis = 0;
                    state++;
                    Mix_PlayChannel(-1, unClick, 0);
                    set_instructions(2,3,bigFont,arrowFont, "VICTOIRE", " ", daColor);
                    Mix_HaltMusic();
                    Mix_PlayMusic(applause,1);
                    if (exoMode) {
                        set_timer(indexTimer);
                    }
                }
                else {
                    combo=0;
                }
			}
			else if (e.key.keysym.sym == SDLK_n) {
                if (((state==1 || state==3) && combo==0) || (state==4 && combo==3)) {
                    combo++;
                    Mix_PlayChannel(-1, onClick, 0);
                }
                else {
                    combo=0;
                }
			}
			else if (e.key.keysym.sym == SDLK_k) {
                if ((state==2 && combo==0) || (state==4 && (combo==0 || combo==5))) {
                    combo++;
                    Mix_PlayChannel(-1, onClick, 0);
                }
                else {
                    combo=0;
                }
			}
			else if (e.key.keysym.sym == SDLK_MINUS || e.key.keysym.sym == SDLK_KP_MINUS || e.key.keysym.sym == SDLK_6) {
                if ((state==4 && combo==4)) {
                    combo++;
                    Mix_PlayChannel(-1, onClick, 0);
                }
                else {
                    combo=0;
                }
			}
			else if (e.key.keysym.sym == SDLK_LEFTPAREN || e.key.keysym.sym == SDLK_KP_LEFTPAREN || e.key.keysym.sym == SDLK_5 || e.key.keysym.sym == SDLK_9) {
                if ((state==4 && combo==2)) {
                    combo++;
                    Mix_PlayChannel(-1, onClick, 0);
                }
                else {
                    combo=0;
                }
			}
			else if (e.key.keysym.sym == SDLK_RIGHTPAREN || e.key.keysym.sym == SDLK_KP_RIGHTPAREN || e.key.keysym.sym == SDLK_0) {
                if ((state==4 && combo==6)) {
                    combo++;
                    Mix_PlayChannel(-1, onClick, 0);
                }
                else {
                    combo=0;
                }
			}
			else if (e.key.keysym.sym == SDLK_EXCLAIM || e.key.keysym.sym == SDLK_KP_EXCLAM) {
                if ((state==3 && combo==1) || (state==4 && (combo==1 || combo==7) )) {
                    combo++;
                    Mix_PlayChannel(-1, onClick, 0);
                }
                else {
                    combo=0;
                }
			}
			else if ((e.key.keysym.sym == SDLK_KP_ENTER || e.key.keysym.sym == SDLK_RETURN) && state==0) {
                set_instructions(2,3,bigFont,arrowFont, instructions[state*2], instructions[state*2+1], daColor);
                state++;
                Mix_PlayChannel(-1, unClick, 0);
			}
			else if (e.key.keysym.sym == SDLK_LSHIFT || e.key.keysym.sym == SDLK_RSHIFT || e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_KP_SPACE) {
			}
			else {
                combo=0;
			}
			break;
    }
}

void draw_lvltemp(void) {
    SDL_RenderClear(gRenderer);
	SDL_RenderCopy(gRenderer, background.texture, NULL, &background.rect);
	for (int i = 0; i < nbTextures; i++) {
		SDL_RenderCopy(gRenderer, vTextures[i].texture, NULL, &vTextures[i].rect);
	}
	for (int i = 0; i < nbButtons; i++) {
		SDL_RenderCopy(gRenderer, bTextures[i].buttonTexture.texture, NULL, &bTextures[i].buttonTexture.rect);
		SDL_RenderCopy(gRenderer, bTextures[i].textTexture.texture, NULL, &bTextures[i].textTexture.rect);
	}
	for (int i = 0; i < nbBlanks; i++) {
        if (blanks[i].vis == 1) {
            SDL_RenderCopy(gRenderer, blanks[i].texture.texture, NULL, &blanks[i].texture.rect);
        }
	}
	SDL_RenderPresent(gRenderer);
}
