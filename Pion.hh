#pragma once
#include <iostream>
#include "Piece.hh"

class Pion : public Piece{
	public:
		Pion(int x, int y, int couleur):Piece(x,y,couleur){
			first=0;
			
			if(_couleur==0)
				_val=1;
			else
				_val=11;
		}
		virtual int occupated(int nx, int ny, int **screen);
		virtual void deplacement(int nx, int ny, int **screen);
		virtual bool allowed(int nx, int ny, int **screen);
		virtual int getVal(){return _val;}

	private:
		int _val;
		bool first;
		
};
