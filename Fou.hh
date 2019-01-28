#pragma once
#include <iostream>
#include "Piece.hh"

class Fou : public Piece{
	public:
		Fou(int x, int y, int couleur):Piece(x,y,couleur){
			
			if(_couleur==0)
				_val=4;
			else
				_val=14;
		}
		virtual int occupated(int nx, int ny, int **screen);
		virtual void deplacement(int nx, int ny, int **screen);
		virtual bool allowed(int nx, int ny, int **screen);
		virtual int getVal(){return _val;}

		int direction(int nx, int ny, int **screen);

	private:
		int _val;
		
};
