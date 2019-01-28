#include "TextureManager.hh"

/*Charge la texture à partir du nom du fichier*/
SDL_Texture* TextureManager::LoadTexture(const char*filename){
	SDL_Surface* Surface = IMG_Load(filename);

	if(Surface == NULL) {
        cerr << "ERROR: image load failed: " << SDL_GetError() << endl;
    }

	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer,Surface);
	SDL_FreeSurface(Surface);

	return tex;
}

/*Dessine la texture sur le renderer*/
void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest){
	SDL_RenderCopy(Game::renderer, tex,NULL, &dest);
}