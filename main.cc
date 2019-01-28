#include <SDL2/SDL.h> 
#include "Game.hh"

Game *game;

int main(int argc,const char * argv[]){
    /*Vitesse du jeu*/
    //const int FPS = 60, FrameDelay = 1000/FPS;
	//Uint32 frameStart;
	//int frameTime;
    
    /*Initialisation du jeu*/
    game = new Game("Chess Game",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640,690);

    /*Boucle de jeu*/
    while(game->getRunning()){
            game->handleEvent();
            game->update();
            game->render();
    	//frameStart = SDL_GetTicks();
        //frameTime = SDL_GetTicks()-frameStart;

        //if(FrameDelay>frameTime){ 
        //	SDL_Delay(FrameDelay-frameTime);
        //}
    }
    return 0; 
}