#pragma once
#include "Game.hh"

class Map{
	public:
		//Constructeur
		Map();

		//Destructeur
		~Map();

		//Fonctions Membres
		void Draw();
	private:
		SDL_Rect src, dest;
		SDL_Texture* beige;
		SDL_Texture* marron;
};