#pragma once
#include <iostream>
#include "Piece.hh"

class Roi : public Piece{
	public:
		Roi(int x, int y, int couleur):Piece(x,y,couleur){
			
			if(_couleur==0)
				_val=6;
			else
				_val=16;

			first=0;
		}
		virtual int occupated(int nx, int ny, int **screen);
		virtual void deplacement(int nx, int ny, int **screen);
		virtual bool allowed(int nx, int ny, int **screen);
		virtual int getVal(){return _val;}

	private:
		int _val;
		bool first;
};
