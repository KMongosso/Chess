#pragma once
#include <iostream>
#include "Piece.hh"

class Tour : public Piece{
	public:
		Tour(int x, int y, int couleur):Piece(x,y,couleur){
			
			if(_couleur==0)
				_val=2;
			else
				_val=12;
		}
		virtual int occupated(int nx, int ny, int **screen);
		virtual void deplacement(int nx, int ny, int **screen);
		virtual bool allowed(int nx, int ny, int **screen);
		virtual int getVal(){return _val;}
		int direction(int nx, int ny, int **screen);

	private:
		int _val;
		
};
