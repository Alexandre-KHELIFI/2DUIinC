//gcc -Wall test.c -o bol -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer $(sdl2-config --cflags --libs)

#include<math.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys\timeb.h>
#include<unistd.h>
#include "UIengine.h"
#include "globals.h"

SDL_Texture* create_texture_from_image (char* path) {

	SDL_Texture *texture = NULL;
	SDL_Surface *surface = IMG_Load(path);
	if (surface == NULL) {
		printf("error load image: %s", IMG_GetError());
		return texture;
	}
	texture = SDL_CreateTextureFromSurface(gRenderer, surface);
	SDL_FreeSurface(surface);
	return texture;

}

Texture create_texture_from_text (TTF_Font* font, char* str, SDL_Color textColor) {

	Texture textTexture;
	SDL_Surface *surface = TTF_RenderText_Blended(font, str, textColor);
	if (surface == NULL) {
		printf("error load text: %s", TTF_GetError());
		return textTexture;
	}
	textTexture.texture = SDL_CreateTextureFromSurface(gRenderer, surface);
	textTexture.rect.h = surface->h;
	textTexture.rect.w = surface->w;
	SDL_FreeSurface(surface);
	return textTexture;

}

void create_text(int compt, int x, int y, SDL_Color color, TTF_Font* font, char* text) {
	Texture textTexture;
	textTexture = create_texture_from_text(font, text, color);
	textTexture.rect.x = x - textTexture.rect.w/2;
	textTexture.rect.y = y - textTexture.rect.h/2;
	vTextures[compt] = textTexture;
	nbTextures++;
}

void create_various_texture(int compt, int x, int y, int w, int h, char* path) {
    SDL_Rect box;
	box.x = x-w/2;
	box.y = y-h/2;
	box.w = w;
	box.h = h;
	Texture texture;
	texture.texture = create_texture_from_image (path);
	texture.rect = box;
	vTextures[compt] = texture;
	nbTextures++;
}

void create_button(int compt, int x, int y,int w, int h, SDL_Color color, TTF_Font* font, char* text, SDL_Texture* textureIdle) {
	SDL_Rect box;
	box.x = x-w/2;
	box.y = y-h/2;
	box.w = w;
	box.h = h;
	bHitboxes[compt].box = box;
	ButtonTexture button;Texture texture;Texture textTexture;
	texture.texture = textureIdle;
	texture.rect = box;
	textTexture = create_texture_from_text(font, text, color);
	textTexture.rect.x = x - textTexture.rect.w/2;
	textTexture.rect.y = y - textTexture.rect.h/2;
	button.buttonTexture = texture;
	button.textTexture = textTexture;
	bTextures[compt] = button;
	nbButtons++;
}

void create_linkM(int x, int y) {
    SDL_Rect box;
    box.x = x-S_HEIGHT/15/2;
	box.y = y-S_HEIGHT/15/2;
	box.w = S_HEIGHT/15;
	box.h = S_HEIGHT/15;
    lmHitboxes[nbLmHitboxes].box = box;
	Texture texture;
	texture.texture = textureLinkM;
	texture.rect = box;
	lTextures[nbLmHitboxes] = texture;
	nbLmHitboxes++;
}

void create_linkF(int x, int y) {
    SDL_Rect box;
    box.x = x-S_HEIGHT/15/2;
	box.y = y-S_HEIGHT/15/2;
	box.w = S_HEIGHT/15;
	box.h = S_HEIGHT/15;
    lfHitboxes[nbLfHitboxes].box = box;
	Texture texture;
	texture.texture = textureLinkF;
	texture.rect = box;
	lTextures[nbLmHitboxes+nbLfHitboxes] = texture;
	nbLfHitboxes++;
}

void create_arrow(void) {
    SDL_Rect box;
    box.x = 0;
	box.y = 0;
	box.w = 0;
	box.h = S_HEIGHT/15;
	Texture texture;
	texture.texture = textureArrow;
	texture.rect = box;
	SDL_Point src = {0,0};
	Arrow arrow;
	arrow.vis=0;
	arrow.texture=texture;
	arrow.angle=0;
    arrow.src=src;
    aTextures[nbArrows]=arrow;
    nbArrows++;
}

void create_blank(int index, int x, int y, int w, int h) {
    blanks[nbBlanks].vis=1;
    SDL_Rect box;
    box.x = x-w/2;
	box.y = y-h/2;
	box.w = w;
	box.h = h;
	Texture texture;
	texture.texture = textureBlank;
	texture.rect = box;
	blanks[nbBlanks].texture = texture;
	nbBlanks++;
}

int get_index_bHitbox_clicked(int x, int y) {
	for (int i=0; i<nbButtons; i++) {
		if (x > bHitboxes[i].box.x && y > bHitboxes[i].box.y &&
			y < bHitboxes[i].box.y+bHitboxes[i].box.h && x < bHitboxes[i].box.x+bHitboxes[i].box.w) {
			return i;
		}
	}
	return -1;
}

int check_bHitbox(int x, int y, int index) {
	if (x > bHitboxes[index].box.x && y > bHitboxes[index].box.y &&
		y < bHitboxes[index].box.y+bHitboxes[index].box.h && x < bHitboxes[index].box.x+bHitboxes[index].box.w) {
		return 1;
	}
	return 0;
}

int get_index_lmHitbox(int x, int y) {
    for (int i=0; i<nbLmHitboxes; i++) {
		if (x > lmHitboxes[i].box.x && y > lmHitboxes[i].box.y &&
			y < lmHitboxes[i].box.y+lmHitboxes[i].box.h && x < lmHitboxes[i].box.x+lmHitboxes[i].box.w) {
			return i;
		}
	}
	return -1;
}

int get_index_lfHitbox(int x, int y) {
    for (int i=0; i<nbLfHitboxes; i++) {
		if (x > lfHitboxes[i].box.x && y > lfHitboxes[i].box.y &&
			y < lfHitboxes[i].box.y+lfHitboxes[i].box.h && x < lfHitboxes[i].box.x+lfHitboxes[i].box.w) {
			return i;
		}
	}
	return -1;
}

void set_text(int index, TTF_Font* font, char* name, SDL_Color color) {
	int x = vTextures[index].rect.x + vTextures[index].rect.w/2;
	int y = vTextures[index].rect.y + vTextures[index].rect.h/2;
	SDL_DestroyTexture(vTextures[index].texture);
	Texture textTexture;
	textTexture = create_texture_from_text(font, name, color);
	textTexture.rect.x = x - textTexture.rect.w/2;
	textTexture.rect.y = y - textTexture.rect.h/2;
	vTextures[index] = textTexture;
}

void write_timers(Uint32* timers, TTF_Font* font) {
    SDL_Color colorDefault = {0,0,0};
    SDL_Color colorToDo = {255,0,0};
    SDL_Color colorDone = {0,255,0};
    SDL_Color colorTooLate = {0,0,255};
    SDL_Color color = colorDefault;
    for (int i=0;i<nbTimers;i++) {
        if (timers[i]!=0) {
            Uint32 time = (SDL_GetTicks() + savedTimers[i] - timers[i])/1000;
            int datime = (int)time;
            int s=datime%60;
            int m=(datime/60)%60;
            int h=((datime/60)/60)%60;
            int d=((datime/60)/60)/24;
            char name[11];name[0]='\0';
            char str[11];
            sprintf(str, "%02d", h);
            strcat(name,str);
            strcat(name,":");
            sprintf(str, "%02d", m);
            strcat(name,str);
            strcat(name,":");
            sprintf(str, "%02d", s);
            strcat(name,str);
            if (timersDone[i]) {
                color = colorDone;
            }
            else if ((m>35 && h<1 && d<1) || (m<=5 && h==1 && d<1)) {
                color = colorToDo;
            }
            else if ((m>5 && h>1) || h>2 || d>1) {
                color = colorTooLate;
            }
            set_text(i*2+1,font,name,color);
            color = colorDefault;
        }
    }
}

void set_timer(int index) {
    Uint32 time = timers[index];
    if (time==0) {
        timers[index] = SDL_GetTicks();
        return;
    }
    else if (timersDone[index]) {
        return;
    }
    time = (SDL_GetTicks() + savedTimers[index] - timers[index])/1000;
    int datime = (int)time;
    int m=(datime/60)%60;
    int h=((datime/60)/60)%60;
    int d=((datime/60)/60)/24;
    if ((m>35 && h<1 && d<1) || (m<=5 && h==1 && d<1)) {
        timersDone[index]=1;
    }
    else {
        timers[index]=SDL_GetTicks();
        savedTimers[index]=0;
    }
}

void set_arrow(int indexS, int indexD,int indexA) {
    if (indexD != -1) {
        int xs = lmHitboxes[indexS].box.x;
        int ys = lmHitboxes[indexS].box.y;
        int xd = lfHitboxes[indexD].box.x;
        int yd = lfHitboxes[indexD].box.y;
        int xdiff = xd-xs;
        int ydiff = yd-ys;
        double size = sqrt((double)(xdiff*xdiff + ydiff*ydiff));
        double angle1 = asin((double)xdiff/size)*180.0/3.14159265;
        if (xdiff>=0 && ydiff>=0) {
            angle1 = 180.0-angle1;
        }
        else if (xdiff<0 && ydiff>=0) {
            angle1 = 180.0-angle1;
        }
        angle1 -= 90.0;
        aTextures[indexA].vis = 1;
        aTextures[indexA].texture.rect.x = xs+(S_HEIGHT/15/2);
        aTextures[indexA].texture.rect.y = ys;
        aTextures[indexA].texture.rect.w = size;
        aTextures[indexA].texture.rect.h = (S_HEIGHT/15);
        aTextures[indexA].src.x = 0;
        aTextures[indexA].src.y = (S_HEIGHT/15/2);
        aTextures[indexA].angle = angle1;
    }
    else {
        aTextures[indexA].vis = 0;
    }
}

void set_arrow_onmouse(int index, int x, int y, int indexA) {
    int xs = lmHitboxes[index].box.x;
    int ys = lmHitboxes[index].box.y;
    int xdiff = x-xs-20;
    int ydiff = y-ys-20;
    double size = sqrt((double)(xdiff*xdiff + ydiff*ydiff));
    double angle1 = asin((double)xdiff/size)*180.0/3.14159265;
    if (xdiff>=0 && ydiff>=0) {
        angle1 = 180.0-angle1;
    }
    else if (xdiff<0 && ydiff>=0) {
        angle1 = 180.0-angle1;
    }
    angle1 -= 90.0;
    aTextures[indexA].vis = 1;
    aTextures[indexA].texture.rect.x = xs+(S_HEIGHT/15/2);
    aTextures[indexA].texture.rect.y = ys;
    aTextures[indexA].texture.rect.w = size;
    aTextures[indexA].texture.rect.h = S_HEIGHT/15;
    aTextures[indexA].src.x = 0;
    aTextures[indexA].src.y = (S_HEIGHT/15/2);
    aTextures[indexA].angle = angle1;
}

void set_instructions(int index1, int index2, TTF_Font* font1, TTF_Font* font2, char* letters, char* arrows, SDL_Color color) {
    if (vTextures[index1].rect.x+vTextures[index1].rect.w/2 != S_WIDTH/2) {
        vTextures[index1].rect.x+=vTextures[index1].rect.w/2;
        vTextures[index2].rect.x-=vTextures[index2].rect.w/2;
    }
    set_text(index1,font1,letters,color);
    set_text(index2,font2,arrows,color);
    if (strcmp(arrows," ")!=0) {
        vTextures[index1].rect.x-=vTextures[index1].rect.w/2;
        vTextures[index2].rect.x+=vTextures[index2].rect.w/2;
    }
}

//more than one arrow at a time
void handle_mickey_mouse(int* quit, int* clickHandlerState, int* indexButton,SDL_Event e, int* oldIndex, void (*redirect)(int,int*),void (*destroy)(void)) {
		int x,y;
		SDL_GetMouseState(&x, &y);
		switch (e.type) {
			case SDL_QUIT:
				//menu specific
				destroy();
				*quit=1;
				break;
			case SDL_MOUSEMOTION:
				if (*clickHandlerState != 1) {
					*oldIndex = *indexButton;
					*indexButton = get_index_bHitbox_clicked(x,y);
					if (*oldIndex != -1) {
						bTextures[*oldIndex].buttonTexture.texture = buttonStates[0];
						*oldIndex = -1;
					}
					if (*indexButton != -1) {
						bTextures[*indexButton].buttonTexture.texture = buttonStates[1];
					}
				}
				if (*clickHandlerState == 1) {
                    if (!check_bHitbox(x,y,*indexButton)) {
                        bTextures[*indexButton].buttonTexture.texture = buttonStates[1];
                    }
                    else {
                        bTextures[*indexButton].buttonTexture.texture = buttonStates[2];
                    }
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				switch (e.button.button) {
					case SDL_BUTTON_LEFT:
					    if (*indexButton == -1) {
                            *indexButton = get_index_bHitbox_clicked(x,y);
					    }
						if (*indexButton != -1 && check_bHitbox(x,y,*indexButton)) {
							bTextures[*indexButton].buttonTexture.texture = buttonStates[2];
							*clickHandlerState = 1;
							Mix_PlayChannel(-1, onClick, 0);
						}
						break;
					case SDL_BUTTON_RIGHT:
						if (*indexButton != -1) {
							bTextures[*indexButton].buttonTexture.texture = buttonStates[0];
							*oldIndex = *indexButton;
							*indexButton = -1;
							*clickHandlerState = 0;
						}
						break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				switch (e.button.button) {
					case SDL_BUTTON_LEFT:
						if (*indexButton != -1 && *clickHandlerState==1) {
							if (check_bHitbox(x,y,*indexButton)) {
								*clickHandlerState = 2;
								Mix_PlayChannel(-1, unClick, 0);
								//menu specific
								redirect(*indexButton, quit);
							}
							else {
								bTextures[*indexButton].buttonTexture.texture = buttonStates[0];
								*oldIndex = *indexButton;
							}
							*indexButton=-1;
                            *clickHandlerState = 0;
						}
						break;
				}
				break;
		}
}

void handle_links (int* indexLinkM, int* indexArrow, SDL_Event e) {
    int x,y;
    SDL_GetMouseState(&x, &y);
    switch (e.type) {
        case SDL_MOUSEMOTION:
			if (*indexLinkM != -1) {
                   set_arrow_onmouse(*indexLinkM,x,y,*indexArrow);            //oops
			}
        case SDL_MOUSEBUTTONDOWN:
            switch (e.button.button) {
                case SDL_BUTTON_LEFT:
                    if (*indexLinkM == -1) {
                    *indexLinkM = get_index_lmHitbox(x,y);
                    if (*indexLinkM == -1) {
                        int ilf = get_index_lfHitbox(x,y);
                        if (ilf !=-1) {
                            for (int i=0;i<nbLmHitboxes;i++) {
                                if (linkIndexes[ilf][i]!=-1) {
                                    *indexLinkM=i;
                                }
                            }
                            *indexArrow = linkIndexes[ilf][*indexLinkM];
                            linkIndexes[ilf][*indexLinkM]=-1;
                            lmCounts[*indexLinkM]-=1;
                        }
                    }
                    else {
                        if (lmCounts[*indexLinkM]<nbLfHitboxes) {
                            for (int i=0;i<nbArrows;i++) {
                                if (aTextures[i].vis==0) {
                                    *indexArrow=i;
                                }
                            }
                        }
                    }
                    if (*indexLinkM != -1 && *indexArrow!=-1) {
                        printf("%d %d\n", *indexLinkM, lmCounts[*indexLinkM]);
                        set_arrow_onmouse(*indexLinkM,x,y,*indexArrow);
                        Mix_PlayChannel(-1, onClick, 0);
                    }
                    else {
                        *indexLinkM = -1;
                        *indexArrow = -1;
                    }
                }
                break;
                case SDL_BUTTON_RIGHT:
                    if (*indexLinkM != -1) {
                        set_arrow(*indexLinkM,-1,*indexArrow);
                        *indexLinkM = -1;
                        *indexArrow = -1;
                    }
                    break;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            switch (e.button.button) {
				case SDL_BUTTON_LEFT:
                    if (*indexLinkM != -1 && *indexArrow!= -1) {
                        int ilf = get_index_lfHitbox(x,y);
                        if (ilf != -1 && linkIndexes[ilf][*indexLinkM]==-1) {
                            linkIndexes[ilf][*indexLinkM]=*indexArrow;
                            set_arrow(*indexLinkM,ilf,*indexArrow);
                            lmCounts[*indexLinkM]+=1;
                            Mix_PlayChannel(-1, unClick, 0);
                        }
                        else {
                            set_arrow(*indexLinkM,-1,*indexArrow);
                        }
                        *indexLinkM = -1;
                        *indexArrow = -1;
                    }
				break;
			}
			break;
    }
}

void handle_textbox (SDL_Event e, TTF_Font* font, int index, char* dastr) {
	int l = strlen(dastr);
	switch(e.type) {
		case SDL_KEYDOWN:
			if( e.key.keysym.sym == SDLK_BACKSPACE && l >0 ) {
				dastr[l-1]='\0';
				//refresh text texture set textbox index
				set_text(index,font,dastr,daColor);
			}
			break;
		case SDL_TEXTINPUT:
			if(l < 26) {
				strcat(dastr,e.text.text);
				//refresh text texture set textbox index
				set_text(index,font,dastr,daColor);
			}
			break;
	}
}

void draw_default(void) {
	SDL_RenderClear(gRenderer);
	SDL_RenderCopy(gRenderer, background.texture, NULL, &background.rect);
	for (int i = 0; i < nbTextures; i++) {
		SDL_RenderCopy(gRenderer, vTextures[i].texture, NULL, &vTextures[i].rect);
	}
	for (int i = 0; i < nbButtons; i++) {
		SDL_RenderCopy(gRenderer, bTextures[i].buttonTexture.texture, NULL, &bTextures[i].buttonTexture.rect);
		SDL_RenderCopy(gRenderer, bTextures[i].textTexture.texture, NULL, &bTextures[i].textTexture.rect);
	}
	SDL_RenderPresent(gRenderer);
}

void save_timers(void) {
    FILE *fptr = fopen("save.dh","w");
    if (fptr == NULL) {
        return;
    }
    long *tab = (long*)malloc(nbTimers * sizeof(long));
    struct timeb t_start;ftime(&t_start);
    long tttt = (long)t_start.time;
    for (int i=0;i<nbTimers;i++) {
        if (timers[i]!=0) {
            tab[i]=(long)(tttt*1000)+t_start.millitm-(long)savedTimers[i]-(long)timers[i];
        }
        else {
            tab[i]=0;
        }
    }
    fwrite(tab, sizeof(long),nbTimers,fptr);
    fwrite(timersDone, sizeof(int),nbTimers,fptr);
    fclose(fptr);
}

void load_timers(void) {
    FILE *fptr = fopen("save.dh","r");
    if (fptr == NULL) {
        return;
    }
    long *tab = (long*)malloc(nbTimers * sizeof(long));
    fread(tab, sizeof(long),nbTimers,fptr);
    fread(timersDone, sizeof(int),nbTimers,fptr);
    fclose(fptr);
    struct timeb t_start;ftime(&t_start);
    long tttt = (long)t_start.time;
    for (int i=0;i<nbTimers;i++) {
        if (tab[i]!=0) {
            savedTimers[i]=(Uint32)(tttt*1000+t_start.millitm-tab[i]);
            timers[i]=1;
        }
    }
}
