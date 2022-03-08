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
#include "levelLogi.h"

void handle_keyboardLogi(SDL_Event e);

void init_lvlLogi(void) {

	nbButtons = 0;int b=2;
	nbTextures = 0;int t=6;
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
	create_text(0,S_WIDTH/2,S_HEIGHT/8,color,font,"Implication");
    create_various_texture(1,S_WIDTH/2,3*S_HEIGHT/10-S_HEIGHT/9/2-S_HEIGHT/120,S_WIDTH/2+S_WIDTH/50,S_HEIGHT/18,"images/formulas/negation.JPG");
    create_various_texture(4,S_WIDTH/2,3*S_HEIGHT/10,S_WIDTH/2+S_WIDTH/50,S_HEIGHT/18-S_HEIGHT/110,"images/formulas/contraposee.JPG");
    create_various_texture(5,S_WIDTH/2,3*S_HEIGHT/10+S_HEIGHT/9/2+S_HEIGHT/120,S_WIDTH/2+S_WIDTH/50,S_HEIGHT/18-S_HEIGHT/120,"images/formulas/reciproque.JPG");
    create_text(2,S_WIDTH/2,6*S_HEIGHT/10,color,bigFont,"ENTER");
    create_text(3,S_WIDTH/2,6*S_HEIGHT/10,color,arrowFont," ");
	//initialize blanks (last to first 0->n)
	create_blank(0,S_WIDTH/2+S_WIDTH/4-S_WIDTH/30, 3*S_HEIGHT/10-S_HEIGHT/9/2-S_HEIGHT/120, S_WIDTH/8, S_HEIGHT/18);
	create_blank(1,S_WIDTH/2+S_WIDTH/4-S_WIDTH/30, 3*S_HEIGHT/10, S_WIDTH/8+S_WIDTH/160, S_HEIGHT/18);
	create_blank(2,S_WIDTH/2+S_WIDTH/4-S_WIDTH/60, 3*S_HEIGHT/10+S_HEIGHT/9/2, S_WIDTH/8+S_WIDTH/160, S_HEIGHT/18);

	instructions = (char **) realloc(instructions, 6*sizeof(char*));
	char* instrs[6] = {"a^Lb"," ","Lb  =>  La"," ","b  =>  a"," "};
	if (exoMode==1) {
        for (int i=0;i<6;i++) {
            instrs[i]=" ";
        }
	}
	for (int j=0;j<6;j++) {
        instructions[j] = (char *) malloc(16 * sizeof(char));
        strcpy(instructions[j],instrs[j]);
    }
    state=0;combo=0;
    indexTimer=8;
}

void destroy_lvlLogi(void) {
	for (int i = 0; i < nbTextures; i++) {
		SDL_DestroyTexture(vTextures[i].texture);
	}
	for (int i = 0; i < nbButtons; i++) {
		SDL_DestroyTexture(bTextures[i].textTexture.texture);
	}
	for (int j=0;j<6;j++) {
        free(instructions[j]);
    }
}

void redirect_lvlLogi(int index, int* quit) {
	switch(index) {
		case 0:
			//init
			destroy_lvlLogi();
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

void update_lvlLogi(int* quit, SDL_Event e) {
	while(SDL_PollEvent(&e) != 0) {
        handle_keyboardLogi(e);
		handle_mickey_mouse(quit,&clickHandlerState,&indexButton,e,&oldIndex,redirect_lvlLogi,destroy_lvlLogi);
	}
}

void handle_keyboardLogi(SDL_Event e) {
    switch(e.type) {
		case SDL_KEYDOWN:
			if (e.key.keysym.sym == SDLK_a) {
                if (state==1 && combo==0) {
                    combo++;
                    Mix_PlayChannel(-1, onClick, 0);
                }
                else if (state==2 && combo==5) {
                    set_instructions(2,3,bigFont,arrowFont, instructions[state*2], instructions[state*2+1], daColor);
                    blanks[state-1].vis = 0;
                    state++;
                    combo=0;
                    Mix_PlayChannel(-1, unClick, 0);
                }
                else if (state==3 && combo==3) {
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
			else if (e.key.keysym.sym == SDLK_b) {
                if ((state==3 && combo==0) || (state==2 && combo==1)) {
                    combo++;
                    Mix_PlayChannel(-1, onClick, 0);
                }
                else if (state==1 && combo==3) {
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
			else if (e.key.keysym.sym == SDLK_l) {
                if ((state==1 && combo==2) || (state==2 && combo==0) || (state==2 && combo==4)) {
                    combo++;
                    Mix_PlayChannel(-1, onClick, 0);
                }
                else {
                    combo=0;
                }
			}
			else if (e.key.keysym.sym == SDLK_EQUALS || e.key.keysym.sym == SDLK_KP_EQUALS) {
                if ((state==2 && combo==2) || (state==3 && combo==1)) {
                    combo++;
                    Mix_PlayChannel(-1, onClick, 0);
                }
                else {
                    combo=0;
                }
			}
			else if (e.key.keysym.sym == SDLK_GREATER || e.key.keysym.sym == SDLK_KP_GREATER || e.key.keysym.sym == SDLK_LESS || e.key.keysym.sym == SDLK_KP_LESS) {
                if ((state==2 && combo==3) || (state==3 && combo==2)) {
                    combo++;
                    Mix_PlayChannel(-1, onClick, 0);
                }
                else {
                    combo=0;
                }
			}
			else if (e.key.keysym.sym == SDLK_CARET || e.key.keysym.sym == SDLK_KP_POWER || e.key.keysym.sym == SDLK_AMPERSAND || e.key.keysym.sym == SDLK_KP_AMPERSAND || e.key.keysym.sym == SDLK_7) {
                if (state==1 && combo==1) {
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

void draw_lvlLogi(void) {
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
