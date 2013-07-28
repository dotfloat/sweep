
#include <SDL/SDL.h>

#include <stdio.h>

#include <sweep.h>

int main(int argc, char *argv[]){
    sweepCmdlineParse(&argc, argv);
    
    sweep_t game = sweepInitGame();
    
    //sweepApplyOptions(game);
    
    sweepNewGame(game, SG_EASY);
    
    int quit = 0;
    
    SDL_Event event;
    
    while(!quit) {
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                
            }
        }
    }
    
    sweepDestroyGame(game);
    
    return 0;
}