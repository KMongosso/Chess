#pragma once
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "TextureManager.hh"
#include "Map.hh"
#include <list>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <string>
#include <SDL2/SDL_ttf.h>
#include "Pion.hh"
#include "Tour.hh"
#include "Fou.hh"
#include "Reine.hh"
#include "Roi.hh"
#include "Cavalier.hh"
#include "Piece.hh"

/*https://freesound.org/people/joshuaempyre/sounds/251461/*/

using namespace std;

class Game{
	public:
		//Constructeur
		Game(const char* title, int x, int y, int width, int height);

		//Destructeur
		~Game();

		//Fonctions Membres
		void handleEvent();

		void update();
		void render();

		void draw();
		bool echec(Piece *roi, int x, int y, int nx, int ny, int val,int **screen);
		bool echec2(Piece *roi, int nx, int ny, int val);
		bool echecmat(Piece *roi);
		bool save(Piece *roi);
		bool save2(Piece *roi);
		bool getRunning(){return isRunning;}

		static SDL_Renderer* renderer;
		static SDL_Event event;

		static TTF_Font *police;
		static SDL_Surface *text;
		static SDL_Rect destText;

	private:
		int _width,_height;		//Dimensions de l'écran
		SDL_Rect src, dest;

		string fichier;
		const char * fichierc;

		SDL_Window *window;
		int **screen;		//Informations relatives à l'écran
		int x,y,nx,ny;
		bool select;
		int iter,tour,winner;

		bool isRunning;		//Indique si le jeu est toujours en cours	 

		SDL_Texture* pionN;
		SDL_Texture* cavN;
		SDL_Texture* fouN;
		SDL_Texture* tourN;
		SDL_Texture* roiN;
		SDL_Texture* reineN; 
		SDL_Texture* pionB;
		SDL_Texture* cavB;
		SDL_Texture* fouB;
		SDL_Texture* tourB;
		SDL_Texture* roiB;
		SDL_Texture* reineB; 

		list <Piece *> listePiece;


};



