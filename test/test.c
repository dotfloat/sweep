
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <stdio.h>

#include <sweep.h>

int main(int argc, char *argv[]){
	sInit(&argc, argv);
        sbBoard_t board = sGetBoard();
        
        int x, y;
        int click_x = -1, click_y = -1, click_btn = -1;
        S_BOOL quit = S_FALSE;
        sState_t state;
        
        SDL_Init(SDL_INIT_EVERYTHING);
        
        SDL_Surface *screen = SDL_SetVideoMode(16*sbGetWidth(board), 16*sbGetHeight(board), 32, SDL_DOUBLEBUF);
        SDL_WM_SetCaption("Sweep test", "Sweep test");
        
        SDL_Event e;
        
        SDL_Surface *tiles = IMG_Load("tiles.jpg");
        if(!tiles) {
            printf("Couldn't load tiles.\n");
            return 0;
        }
        
        while(!quit) {
            while(SDL_PollEvent(&e)) {
                switch(e.type) {
                    case SDL_MOUSEBUTTONDOWN:
                        click_x = e.button.x/16;
                        click_y = e.button.y/16;
                        if(e.button.button == SDL_BUTTON_LEFT) {
                            click_btn = 0;
                        } else if(e.button.button == SDL_BUTTON_RIGHT) {
                            click_btn = 1;
                        }
                        break;
                    case SDL_MOUSEBUTTONUP:
                        click_x = -1;
                        click_y = -1;
                        click_btn = -1;
                        break;
                    case SDL_QUIT:
                        quit = S_TRUE;
                        break;
                }
            }
            
            switch(sGetState()) {
                case S_RENDER:
                    for(y=0; y<sbGetHeight(board); y++) {
                        for(x=0; x<sbGetWidth(board); x++) {
                            sbLinear_t c = sbGetCellVisible(board, x, y);
                            SDL_Rect src = {0, 0, 16, 16};
                                if(c == SB_L_CLOSED) { src.x = 0; src.y = 0; }
                            else if(c == SB_L_FLAG)   { src.x = 1; src.y = 0; }
                            else if(c == SB_BOMB)     { src.x = 2; src.y = 0; }
                            else if(c == SB_EMPTY)    { src.x = 3; src.y = 0; }
                            else if(c >= SB_1 && c <= SB_8){
                                src.x = (c - SB_1)%4;
                                src.y = (c - SB_1)/4+1;
                            }
                            
                            src.x *= 16;
                            src.y *= 16;
                            
                            SDL_Rect dst = {x*16, y*16, 0, 0};
                            SDL_BlitSurface(tiles, &src, screen, &dst);
                        }
                    }
                    SDL_Flip(screen);
                    
                    break;
                case S_ACTION:
                    if(click_x >= 0 && click_y >= 0 && click_btn >= 0) {
                        if(click_btn == 0) {
                            sReveal(click_x, click_y);
                        } else if (click_btn == 1) {
                            sToggleFlag(click_x, click_y);
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        
        SDL_FreeSurface(tiles);
        SDL_Quit();
        sQuit();
        
        printf("Quated\n");

	return 0;
}
