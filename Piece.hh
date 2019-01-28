#pragma once
#include <iostream>

using namespace std;

class Piece{
	public:
		Piece(int x, int y, int couleur);
		~Piece(){}

		virtual void deplacement(int nx, int ny, int **screen) = 0;
		virtual int occupated(int nx, int ny, int **screen) = 0;
		virtual bool allowed(int nx, int ny, int **screen) = 0;
		virtual int getVal() = 0;

		int getX(){return _x;}
		int getY(){return _y;}
		int getCouleur(){return _couleur;}


	protected:
		int _x;
		int _y;	
		int _couleur;
};