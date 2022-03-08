//gcc -Wall test.c -o bol -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer $(sdl2-config --cflags --libs)
#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include "globals.h"

SDL_Window* gWindow;
SDL_Renderer* gRenderer;
Texture background;

Hitbox* bHitboxes;
ButtonTexture* bTextures;
int nbButtons;
int clickHandlerState;
int indexButton;
int oldIndex;

Texture* vTextures;
int nbTextures;

Hitbox* lmHitboxes;
Hitbox* lfHitboxes;
Texture* lTextures;
int nbLmHitboxes;
int nbLfHitboxes;
int** linkIndexes;
int* lmCounts;
Arrow* aTextures;
int nbArrows;
int indexLinkM;
int indexArrow;

Blank* blanks;
int nbBlanks;

char** instructions;

SDL_Texture** buttonStates;
char* name;
void (*UIupdate)(int*, SDL_Event);
void (*UIdraw)(void);

TTF_Font* bigFont;
TTF_Font* font;
TTF_Font* arrowFont;
Mix_Music* gMusic;
Mix_Chunk* onClick;
Mix_Chunk* unClick;

SDL_Texture* textureIdle;
SDL_Texture* textureLinkM;
SDL_Texture* textureLinkF;
SDL_Texture* textureArrow;
SDL_Texture* textureBlank;

Uint32* timers;
int* timersDone;
Uint32* savedTimers;
int nbTimers;
int indexTimer;
int exoMode;

SDL_Color daColor;

Mix_Music* applause;

SDL_Texture* create_texture_from_image (char* path);
Texture create_texture_from_text (TTF_Font* font, char* str, SDL_Color textColor);
void create_text(int compt, int x, int y, SDL_Color color, TTF_Font* font, char* text);
void create_various_texture(int compt, int x, int y, int w, int h, char* path);
void create_button(int compt, int x, int y,int w, int h, SDL_Color color, TTF_Font* font, char* text, SDL_Texture* textureIdle);
void create_linkM(int x, int y);
void create_linkF(int x, int y);
void create_arrow(void);
void create_blank(int index, int x, int y, int w, int h);

int get_index_bHitbox_clicked(int x, int y);
int get_index_lmHitbox(int x, int y);
int get_index_lfHitbox(int x, int y);
int check_bHitbox(int x, int y, int index);

void set_text(int index, TTF_Font* font, char* name, SDL_Color color);
void write_timers(Uint32* timers, TTF_Font* font);
void set_timer(int index);
void set_arrow(int indexS, int indexD,int indexA);
void set_arrow_onmouse(int index, int x, int y,int indexA);
void set_instructions(int index1, int index2, TTF_Font* font1, TTF_Font* font2, char* letters, char* , SDL_Color color);

void handle_mickey_mouse(int* quit, int* clickHandlerState, int* indexButton,SDL_Event e, int* oldIndex, void (*redirect)(int,int*),void (*destroy)(void));
void handle_links (int* indexLinkM, int* indexArrow, SDL_Event e);
void handle_textbox (SDL_Event e, TTF_Font* font, int index, char* dastr);

void draw_default(void);

void save_timers(void);
void load_timers(void);

#endif // ENGINE_H_INCLUDED
