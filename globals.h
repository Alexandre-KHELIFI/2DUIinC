#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

#define S_WIDTH 800
#define S_HEIGHT 600

typedef struct {
		SDL_Texture* texture;
		SDL_Rect rect;
	}Texture;

typedef struct {
		Texture buttonTexture;
		Texture textTexture;
	}ButtonTexture;

typedef struct {
		SDL_Rect box;
	}Hitbox;

typedef struct {
        int vis;
        Texture texture;
        double angle;
        SDL_Point src;
    }Arrow;

typedef struct {
        int vis;
        Texture texture;
    }Blank;

//UIengine
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern Texture background;

extern Hitbox* bHitboxes;
extern ButtonTexture* bTextures;
extern int nbButtons;
//updates
extern int clickHandlerState;
extern int indexButton;
extern int oldIndex;

extern Texture* vTextures;
extern int nbTextures;

extern Hitbox* lmHitboxes;
extern Hitbox* lfHitboxes;
extern Texture* lTextures;
extern int nbLmHitboxes;
extern int nbLfHitboxes;
extern int** linkIndexes;   //avec linkIndexes[linkF][linkM] = indexArrow
extern int* lmCounts;       //avec lmCounts[linkM] = nbArrowsLeft
extern Arrow* aTextures;
extern int nbArrows;
//updates
extern int indexLinkM;
extern int indexArrow;

extern Texture* blankTextures;
extern int nbBlanks;

extern char** instructions;

extern SDL_Texture** buttonStates;
extern char* name;
extern void (*update)(int*, SDL_Event );
extern void (*draw)(void);

extern TTF_Font* bigFont;
extern TTF_Font* font;
extern TTF_Font* arrowFont;
extern Mix_Music* gMusic;
extern Mix_Chunk* onClick;
extern Mix_Chunk* unClick;
extern int mPause;

//main
extern SDL_Texture* textureIdle;
extern SDL_Texture* textureLinkM;
extern SDL_Texture* textureLinkF;
extern SDL_Texture* textureArrow;
extern SDL_Texture* textureBlank;

extern Uint32* timers;
extern int* timersDone;
extern Uint32* savedTimers;
extern int nbTimers;
extern int indexTimer;
extern int exoMode;

extern SDL_Color daColor;

extern Mix_Music* applause;

#endif // GLOBALS_H_INCLUDED
