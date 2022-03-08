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
#include "levelRestesChinois.h"

void handle_keyboardRestesChinois(SDL_Event e);

void init_lvlRestesChinois(void) {

	nbButtons = 0;int b=2;
	nbTextures = 0;int t=7;
	nbBlanks = 0;int bl=8;
	bHitboxes = (Hitbox *) realloc(bHitboxes,b * sizeof(Hitbox));
	bTextures = (ButtonTexture *) realloc(bTextures,b * sizeof(ButtonTexture));
	vTextures = (Texture *) realloc(vTextures,t * sizeof(Texture));
	blanks = (Blank *) realloc(blanks,bl * sizeof(Blank));

	daColor.r = 0;daColor.g = 0;daColor.b = 0;daColor.a = 255;
	SDL_Color color = {0,0,0};

	//initialize buttons
	create_button(0,S_WIDTH/2,5*S_HEIGHT/6,S_WIDTH/4,S_HEIGHT/15,color,font,"Quit",textureIdle);
	create_button(1,S_WIDTH-(S_HEIGHT/15/2),S_HEIGHT/30,S_HEIGHT/15,S_HEIGHT/15,color,font,"M",textureIdle);
	//initialize various textures/texts
	create_text(0,S_WIDTH/2,S_HEIGHT/11,color,font,"REstes  chinois");
    create_various_texture(1,S_WIDTH/2,3*S_HEIGHT/10-S_HEIGHT/9,S_WIDTH/2+S_WIDTH/4,S_HEIGHT/9+S_HEIGHT/120,"images/formulas/rc1.JPG");
    create_various_texture(4,S_WIDTH/2,3*S_HEIGHT/10-S_HEIGHT/120,S_WIDTH/2+S_WIDTH/4+S_WIDTH/15,S_HEIGHT/18+S_HEIGHT/80,"images/formulas/rc2.JPG");
    create_various_texture(5,S_WIDTH/2,3*S_HEIGHT/10+S_HEIGHT/9-S_HEIGHT/18,S_WIDTH/2+S_WIDTH/4,S_HEIGHT/18+S_HEIGHT/80 ,"images/formulas/rc3.JPG");
    create_various_texture(6,S_WIDTH/2,3*S_HEIGHT/10+2*S_HEIGHT/9-S_HEIGHT/36,S_WIDTH/2+S_WIDTH/4+S_WIDTH/5,S_HEIGHT/9+S_HEIGHT/10,"images/formulas/rc4.JPG");
    create_text(2,S_WIDTH/2,7*S_HEIGHT/10,color,bigFont,"ENTER");
    create_text(3,S_WIDTH/2,7*S_HEIGHT/10,color,arrowFont," ");
	//initialize blanks (last to first 0->n)
	create_blank(0,S_WIDTH/2-S_WIDTH/4, 3*S_HEIGHT/10+S_HEIGHT/9-S_HEIGHT/18, S_WIDTH/8, S_HEIGHT/18);
	create_blank(1,S_WIDTH/2-S_WIDTH/140, 3*S_HEIGHT/10+S_HEIGHT/9-S_HEIGHT/18, S_WIDTH/8, S_HEIGHT/18);
	create_blank(2,S_WIDTH/2+S_WIDTH/3-S_WIDTH/60, 3*S_HEIGHT/10+S_HEIGHT/9-S_HEIGHT/18, S_WIDTH/8, S_HEIGHT/18);
	create_blank(3,S_WIDTH/2+S_WIDTH/3-S_WIDTH/40, 3*S_HEIGHT/10+S_HEIGHT/8, S_WIDTH/6-S_WIDTH/80, S_HEIGHT/18);
	create_blank(4,S_WIDTH/2-S_WIDTH/6, 3*S_HEIGHT/10+S_HEIGHT/5-S_HEIGHT/80, S_WIDTH/5+S_WIDTH/120, S_HEIGHT/18);
	create_blank(5,S_WIDTH/2+S_WIDTH/22, 3*S_HEIGHT/10+S_HEIGHT/5-S_HEIGHT/80, S_WIDTH/5, S_HEIGHT/18);
	create_blank(6,S_WIDTH/2+S_WIDTH/4-S_WIDTH/120, 3*S_HEIGHT/10+S_HEIGHT/4+S_HEIGHT/60, S_WIDTH/4, S_HEIGHT/18);
	create_blank(7,S_WIDTH/2+S_WIDTH/3+S_WIDTH/11, 3*S_HEIGHT/10+S_HEIGHT/4+S_HEIGHT/60, S_WIDTH/8, S_HEIGHT/18);

	instructions = (char **) realloc(instructions, 16*sizeof(char*));
	char* instrs[16] = {"a  mod  p"," ","b  mod  q"," ","c  mod  pq"," ","up  +  vq  =  1"," ","c = avq  +  bup"," ","mod  pq"," ","c = a +  (b-a)up"," ","mod  pq"," "};
	if (exoMode==1) {
        for (int i=0;i<16;i++) {
            instrs[i]=" ";
        }
	}
	for (int j=0;j<16;j++) {
        instructions[j] = (char *) malloc(16 * sizeof(char));
        strcpy(instructions[j],instrs[j]);
    }
    state=0;combo=0;
    indexTimer=9;
}

void destroy_lvlRestesChinois(void) {
	for (int i = 0; i < nbTextures; i++) {
		SDL_DestroyTexture(vTextures[i].texture);
	}
	for (int i = 0; i < nbButtons; i++) {
		SDL_DestroyTexture(bTextures[i].textTexture.texture);
	}
	for (int j=0;j<16;j++) {
        free(instructions[j]);
    }
}

void redirect_lvlRestesChinois(int index, int* quit) {
	switch(index) {
		case 0:
			//init
			destroy_lvlRestesChinois();
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

void update_lvlRestesChinois(int* quit, SDL_Event e) {
	while(SDL_PollEvent(&e) != 0) {
        handle_keyboardRestesChinois(e);
		handle_mickey_mouse(quit,&clickHandlerState,&indexButton,e,&oldIndex,redirect_lvlRestesChinois,destroy_lvlRestesChinois);
	}
}

void handle_keyboardRestesChinois(SDL_Event e) {
    switch(e.type) {
		case SDL_KEYDOWN:
			if (e.key.keysym.sym == SDLK_a) {
                if ((state==1 && combo==0) || (state==5 && combo==2) || (state==7 && combo==2) || (state==7 && combo==7)) {
                    combo++;
                    Mix_PlayChannel(-1, onClick, 0);
                }
                else {
                    combo=0;
                }
			}
			else if (e.key.keysym.sym == SDLK_b) {
                if ((state==2 && combo==0) || (state==5 && combo==6) || (state==7 && combo==5)) {
                    combo++;
                    Mix_PlayChannel(-1, onClick, 0);
                }
                else {
                    combo=0;
                }
			}
			else if (e.key.keysym.sym == SDLK_c) {
                if ((state==3 && combo==0) || (state==5 && combo==0) || (state==7 && combo==0)) {
                    combo++;
                    Mix_PlayChannel(-1, onClick, 0);
                }
                else {
                    combo=0;
                }
			}
			else if (e.key.keysym.sym == SDLK_u) {
                if ((state==4 && combo==0) || (state==5 && combo==7) || (state==7 && combo==9)) {
                    combo++;
                    Mix_PlayChannel(-1, onClick, 0);
                }
                else {
                    combo=0;
                }
			}
			else if (e.key.keysym.sym == SDLK_v) {
                if ((state==4 && combo==3) || (state==5 && combo==3)) {
                    combo++;
                    Mix_PlayChannel(-1, onClick, 0);
                }
                else {
                    combo=0;
                }
			}
			else if (e.key.keysym.sym == SDLK_p) {
                if ((state==3 && combo==4) || (state==4 && combo==1) || (state==6 && combo==3) || (state==8 && combo==3)) {
                    combo++;
                    Mix_PlayChannel(-1, onClick, 0);
                }
                else if ((state==1 && combo==4) || (state==5 && combo==8) || (state==7 && combo==10)) {
                    set_instructions(2,3,bigFont,arrowFont, instructions[state*2], instructions[state*2+1], daColor);
                    blanks[state-1].vis = 0;
                    state++;
                    combo=0;
                    Mix_PlayChannel(-1, unClick, 0);
                }
                else {
                    combo=0;
                }
			}
			else if (e.key.keysym.sym == SDLK_q) {
                if ((state==4 && combo==4) || (state==5 && combo==4)) {
                    combo++;
                    Mix_PlayChannel(-1, onClick, 0);
                }
                else if ((state==2 && combo==4) || (state==3 && combo==5) || (state==6 && combo==4)) {
                    set_instructions(2,3,bigFont,arrowFont, instructions[state*2], instructions[state*2+1], daColor);
                    blanks[state-1].vis = 0;
                    state++;
                    combo=0;
                    Mix_PlayChannel(-1, unClick, 0);
                }
                else if ((state==8 && combo==4)) {
                    blanks[state-1].vis = 0;
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
			else if (e.key.keysym.sym == SDLK_m) {
                if ((state==1 && combo==1) || (state==2 && combo==1) || (state==3 && combo==1) || (state==6 && combo==0) || (state==8 && combo==0)) {
                    combo++;
                    Mix_PlayChannel(-1, onClick, 0);
                }
                else {
                    combo=0;
                }
			}
			else if (e.key.keysym.sym == SDLK_o) {
                if ((state==1 && combo==2) || (state==2 && combo==2) || (state==3 && combo==2) || (state==6 && combo==1) || (state==8 && combo==1)) {
                    combo++;
                    Mix_PlayChannel(-1, onClick, 0);
                }
                else {
                    combo=0;
                }
			}
			else if (e.key.keysym.sym == SDLK_d) {
                if ((state==1 && combo==3) || (state==2 && combo==3) || (state==3 && combo==3) || (state==6 && combo==2) || (state==8 && combo==2)) {
                    combo++;
                    Mix_PlayChannel(-1, onClick, 0);
                }
                else {
                    combo=0;
                }
			}
			else if (e.key.keysym.sym == SDLK_1 || e.key.keysym.sym == SDLK_KP_1) {
                if (state==4 && combo==6) {
                    set_instructions(2,3,bigFont,arrowFont, instructions[state*2], instructions[state*2+1], daColor);
                    blanks[state-1].vis = 0;
                    state++;
                    combo=0;
                    Mix_PlayChannel(-1, unClick, 0);
                }
                else {
                    combo=0;
                }
			}
			else if (e.key.keysym.sym == SDLK_MINUS || e.key.keysym.sym == SDLK_KP_MINUS || e.key.keysym.sym == SDLK_6) {
                if ((state==7 && combo==6)) {
                    combo++;
                    Mix_PlayChannel(-1, onClick, 0);
                }
                else {
                    combo=0;
                }
			}
			else if (e.key.keysym.sym == SDLK_PLUS || e.key.keysym.sym == SDLK_KP_PLUS || e.key.keysym.sym == SDLK_EQUALS || e.key.keysym.sym == SDLK_KP_EQUALS) {
                if ((state==4 && combo==2) || (state==5 && combo==5) || (state==7 && combo==3) || (state==4 && combo==5) || (state==5 && combo==1) || (state==7 && combo==1)) {
                    combo++;
                    Mix_PlayChannel(-1, onClick, 0);
                }
                else {
                    combo=0;
                }
			}
			else if (e.key.keysym.sym == SDLK_LEFTPAREN || e.key.keysym.sym == SDLK_KP_LEFTPAREN || e.key.keysym.sym == SDLK_5 || e.key.keysym.sym == SDLK_9) {
                if ((state==7 && combo==4)) {
                    combo++;
                    Mix_PlayChannel(-1, onClick, 0);
                }
                else {
                    combo=0;
                }
			}
			else if (e.key.keysym.sym == SDLK_RIGHTPAREN || e.key.keysym.sym == SDLK_KP_RIGHTPAREN || e.key.keysym.sym == SDLK_0) {
                if ((state==7 && combo==8)) {
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

void draw_lvlRestesChinois(void) {
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
