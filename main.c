#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<string.h>
#include<stdio.h>
#include <stdlib.h>
#include <sys\timeb.h>
#include <unistd.h>
#include "UIengine.h"
#include "globals.h"
#include "mainmenu.h"

int main (int argc, char *argv[]) {

	gWindow = NULL;
	gRenderer = NULL;
	if (0 != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_TIMER)) {
		printf("%s", SDL_GetError());
		goto Quit;
	}
	gWindow = SDL_CreateWindow("DA GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, S_WIDTH, S_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL) {
		printf("%s", SDL_GetError());
		goto Quit;
	}
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	TTF_Init();
	bigFont = TTF_OpenFont("fonts/theboldfont.ttf", 72);
	font = TTF_OpenFont("fonts/theboldfont.ttf", 14);
	arrowFont = TTF_OpenFont("fonts/Arrows.ttf", 72);
	if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 1024) < 0 ) {
        	printf("%s", Mix_GetError() );
        }
	gMusic = Mix_LoadMUS("DAONSS/blastrisa.mp3");
	applause = Mix_LoadMUS("DAONSS/applause.mp3");
	onClick = Mix_LoadWAV("DAONSS/onClick.wav");
	unClick = Mix_LoadWAV("DAONSS/unClick.wav");
	Mix_PlayMusic(gMusic, -1);
	mPause=0;

	nbTimers = 10;
	timers = (Uint32*)malloc(nbTimers * sizeof(Uint32));
	memset(timers,0,nbTimers * sizeof(Uint32));
	savedTimers = (Uint32*)malloc(nbTimers * sizeof(Uint32));
	memset(savedTimers,0,nbTimers * sizeof(Uint32));
	timersDone = (int*)malloc(nbTimers * sizeof(int));
	memset(timersDone,0,nbTimers * sizeof(int));
	load_timers();

	background.texture = create_texture_from_image("images/background.png");
	background.rect.x = 0;
	background.rect.y = 0;
	background.rect.w = S_WIDTH;
	background.rect.h = S_HEIGHT;

    buttonStates = (SDL_Texture**)realloc (buttonStates, 3*sizeof(SDL_Texture*));
	buttonStates[0] = create_texture_from_image("images/buttons/idle.png");
	buttonStates[1] = create_texture_from_image("images/buttons/mouseOver.png");
	buttonStates[2] = create_texture_from_image("images/buttons/mouseClick.png");
	textureIdle = buttonStates[0];

    textureLinkM = create_texture_from_image("images/buttons/idle.png");
    textureLinkF = create_texture_from_image("images/buttons/idle.png");
    textureArrow = create_texture_from_image("images/arrow.png");
    textureBlank = create_texture_from_image("images/background.png");

	name = (char *) malloc(26 * sizeof(char));
	strcpy(name, "TEST");

	UIupdate = update_menu;
	UIdraw = draw_default;

	SDL_Event e;int quit = 0;
	clickHandlerState = 0;indexButton = -1;oldIndex = -1;
	indexLinkM = -1;indexArrow = -1;

	init_menu();
	while (quit != 1) {
		UIupdate(&quit, e);
		UIdraw();
	}

Quit:

    save_timers();
	SDL_DestroyTexture(background.texture);
	for (int i =0;i<3;i++) {
		SDL_DestroyTexture(buttonStates[i]);
	}
    SDL_DestroyTexture(textureLinkM);
    SDL_DestroyTexture(textureLinkF);
    SDL_DestroyTexture(textureArrow);
    SDL_DestroyTexture(textureBlank);
	free(buttonStates);
	free(bHitboxes);
	free(bTextures);
	free(vTextures);
	free(lmHitboxes);
	free(lfHitboxes);
	free(lTextures);
	free(linkIndexes);
	free(lmCounts);
	free(aTextures);
	free(instructions);
	free(timers);
	background.texture = NULL;
	if (gRenderer != NULL) {
		SDL_DestroyRenderer(gRenderer);
		gRenderer = NULL;
	}
	if (gWindow != NULL) {
		SDL_DestroyWindow(gWindow);
		gWindow = NULL;
	}
	Mix_FreeMusic(gMusic);
	Mix_FreeMusic(applause);
	Mix_FreeChunk(onClick);
	Mix_FreeChunk(unClick);
	Mix_Quit();
	TTF_CloseFont(bigFont);
	TTF_CloseFont(font);
	TTF_CloseFont(arrowFont);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;

}
