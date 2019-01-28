#include "Map.hh"

//////////////////*Costructeur*//////////////////

Map::Map(){
	/*On stockera toutes les textures dans un vecteur ça évitera le switch case dans Draw*/
	beige = TextureManager::LoadTexture("Images/beige.png");
	marron = TextureManager::LoadTexture("Images/marron.png");


	src.x = src.y = 0;
	src.w = dest.w = 80;	/*Dimensions de chaque élément du fond */
	src.h = dest.h = 80;
 	dest.x = dest.y = 0;
}

//////////////////*Destructeur*//////////////////

Map::~Map(){

}

//////////////////*Fonctions Membres*//////////////////


void Map::Draw(){
	bool color;
	for(int i=0;i<8;i++){
		if(i%2==0)
			color=1;
		else
			color=0;
		for(int j=0;j<8;j++){
			dest.x = j*dest.w;
			dest.y = 50+i*dest.h;
			if(color){
				TextureManager::Draw(beige,src,dest);
				color=0;
			}
			else{
				TextureManager::Draw(marron,src,dest);
				color=1;
			}
				

			
		}
	}

}