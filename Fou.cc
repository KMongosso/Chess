#include "Fou.hh"

void Fou::deplacement(int nx, int ny, int **screen){
	screen[_y][_x]=0;
	
	if(_couleur==0)
		_val=4;
	else
		_val=14;

	_x=nx;
	_y=ny;
	screen[_y][_x]=_val;
}

bool Fou::allowed(int nx, int ny, int **screen){
	bool allowed=0;
	
	if((occupated(nx,ny,screen)==0 || occupated(nx,ny,screen)==2) && (abs(nx-_x)>0 && abs(ny-_y)==abs(nx-_x))){
		allowed=1;
	}

	return allowed;
}

int Fou::direction(int nx, int ny, int **screen){
	if(nx-_x<0 && ny-_y<0)
		return 1;
	else if (nx-_x>0 && ny-_y<0)
		return 2;
	else if (nx-_x>0 && ny-_y>0)
		return 3;
	else
		return 4;
}

int Fou::occupated(int nx, int ny, int **screen){
	int occ=0;

	if(_couleur==0){
			//si la case est occupée
		if(direction(nx,ny,screen)==1)
		{
			for(int i=1;i<=_x-nx;i++){
				if(screen[_y-i][_x-i]==1||screen[_y-i][_x-i]==2||screen[_y-i][_x-i]==3||screen[_y-i][_x-i]==4||screen[_y-i][_x-i]==5||screen[_y-i][_x-i]==6)	//si il y a une piece noire sur le chemin 
					occ=1;
				else if ((screen[_y-i][_x-i]==11||screen[_y-i][_x-i]==12||screen[_y-i][_x-i]==13||screen[_y-i][_x-i]==14||screen[_y-i][_x-i]==15||screen[_y-i][_x-i]==16) && i!=_x-nx)
					occ=1;
				else if	((screen[_y-i][_x-i]==11||screen[_y-i][_x-i]==12||screen[_y-i][_x-i]==13||screen[_y-i][_x-i]==14||screen[_y-i][_x-i]==15||screen[_y-i][_x-i]==16) && i==_x-nx && occ==0)		//si la case d'arrivee est occupée par un pion blanc
					occ=2;
			}	
		}
		else if(direction(nx,ny,screen)==2)
		{
			for(int i=1;i<=nx-_x;i++){
				if(screen[_y-i][_x+i]==1||screen[_y-i][_x+i]==2||screen[_y-i][_x+i]==3||screen[_y-i][_x+i]==4||screen[_y-i][_x+i]==5||screen[_y-i][_x+i]==6)	//si il y a une piece noire sur le chemin 
					occ=1;
				else if ((screen[_y-i][_x+i]==11||screen[_y-i][_x+i]==12||screen[_y-i][_x+i]==13||screen[_y-i][_x+i]==14||screen[_y-i][_x+i]==15||screen[_y-i][_x+i]==16) && i!=nx-_x)
					occ=1;
				else if	((screen[_y-i][_x+i]==11||screen[_y-i][_x+i]==12||screen[_y-i][_x+i]==13||screen[_y-i][_x+i]==14||screen[_y-i][_x+i]==15||screen[_y-i][_x+i]==16) && i==nx-_x && occ==0)		//si la case d'arrivee est occupée par un pion blanc
					occ=2;
			}	
		}
		else if(direction(nx,ny,screen)==3)
		{
			for(int i=1;i<=nx-_x;i++){
				if(screen[_y+i][_x+i]==1||screen[_y+i][_x+i]==2||screen[_y+i][_x+i]==3||screen[_y+i][_x+i]==4||screen[_y+i][_x+i]==5||screen[_y+i][_x+i]==6)	//si il y a une piece noire sur le chemin 
					occ=1;
				else if ((screen[_y+i][_x+i]==11||screen[_y+i][_x+i]==12||screen[_y+i][_x+i]==13||screen[_y+i][_x+i]==14||screen[_y+i][_x+i]==15||screen[_y+i][_x+i]==16) && i!=nx-_x)
					occ=1;
				else if	((screen[_y+i][_x+i]==11||screen[_y+i][_x+i]==12||screen[_y+i][_x+i]==13||screen[_y+i][_x+i]==14||screen[_y+i][_x+i]==15||screen[_y+i][_x+i]==16) && i==nx-_x && occ==0)		//si la case d'arrivee est occupée par un pion blanc
					occ=2;
			}	
		}
		else if(direction(nx,ny,screen)==4)
		{
			for(int i=1;i<=_x-nx;i++){
				if(screen[_y+i][_x-i]==1||screen[_y+i][_x-i]==2||screen[_y+i][_x-i]==3||screen[_y+i][_x-i]==4||screen[_y+i][_x-i]==5||screen[_y+i][_x-i]==6)	//si il y a une piece noire sur le chemin 
					occ=1;
				else if ((screen[_y+i][_x-i]==11||screen[_y+i][_x-i]==12||screen[_y+i][_x-i]==13||screen[_y+i][_x-i]==41||screen[_y+i][_x-i]==15||screen[_y+i][_x-i]==16) && i!=_x-nx)
					occ=1;
				else if	((screen[_y+i][_x-i]==11||screen[_y+i][_x-i]==12||screen[_y+i][_x-i]==13||screen[_y+i][_x-i]==41||screen[_y+i][_x-i]==15||screen[_y+i][_x-i]==16) && i==_x-nx && occ==0)		//si la case d'arrivee est occupée par un pion blanc
					occ=2;
			}	
		}
	}
	else{
		if(direction(nx,ny,screen)==1)
		{
			for(int i=1;i<=_x-nx;i++){
				if(screen[_y-i][_x-i]==11||screen[_y-i][_x-i]==12||screen[_y-i][_x-i]==13||screen[_y-i][_x-i]==14||screen[_y-i][_x-i]==15||screen[_y-i][_x-i]==16)	//si il y a une piece blance sur le chemin 
					occ=1;
				else if ((screen[_y-i][_x-i]==1||screen[_y-i][_x-i]==2||screen[_y-i][_x-i]==3||screen[_y-i][_x-i]==4||screen[_y-i][_x-i]==5||screen[_y-i][_x-i]==6) && i!=_x-nx)
					occ=1;
				else if	((screen[_y-i][_x-i]==1||screen[_y-i][_x-i]==2||screen[_y-i][_x-i]==3||screen[_y-i][_x-i]==4||screen[_y-i][_x-i]==5||screen[_y-i][_x-i]==6) && i==_x-nx && occ==0)		//si la case d'arrivee est occupée par un pion noir
					occ=2;
			}	
		}
		else if(direction(nx,ny,screen)==2)
		{
			for(int i=1;i<=nx-_x;i++){
				if(screen[_y-i][_x+i]==11||screen[_y-i][_x+i]==12||screen[_y-i][_x+i]==13||screen[_y-i][_x+i]==14||screen[_y-i][_x+i]==15||screen[_y-i][_x+i]==16 )	//si il y a une piece blanche sur le chemin 
					occ=1;
				else if ((screen[_y-i][_x+i]==1||screen[_y-i][_x+i]==2||screen[_y-i][_x+i]==3||screen[_y-i][_x+i]==4||screen[_y-i][_x+i]==5||screen[_y-i][_x+i]==6) && i!=nx-_x)
					occ=1;
				else if	((screen[_y-i][_x+i]==1||screen[_y-i][_x+i]==2||screen[_y-i][_x+i]==3||screen[_y-i][_x+i]==4||screen[_y-i][_x+i]==5||screen[_y-i][_x+i]==6) && i==nx-_x && occ==0)		//si la case d'arrivee est occupée par un pion noir
					occ=2;
			}	

		}
		else if(direction(nx,ny,screen)==3)
		{
			for(int i=1;i<=nx-_x;i++){
				if(screen[_y+i][_x+i]==11||screen[_y+i][_x+i]==12||screen[_y+i][_x+i]==13||screen[_y+i][_x+i]==14||screen[_y+i][_x+i]==15||screen[_y+i][_x+i]==16)	//si il y a une piece blanche sur le chemin 
					occ=1;
				else if ((screen[_y+i][_x+i]==1||screen[_y+i][_x+i]==2||screen[_y+i][_x+i]==3||screen[_y+i][_x+i]==4||screen[_y+i][_x+i]==5||screen[_y+i][_x+i]==6) && i!=nx-_x)
					occ=1;
				else if	((screen[_y+i][_x+i]==1||screen[_y+i][_x+i]==2||screen[_y+i][_x+i]==3||screen[_y+i][_x+i]==4||screen[_y+i][_x+i]==5||screen[_y+i][_x+i]==6) && i==nx-_x && occ==0)		//si la case d'arrivee est occupée par un pion noir
					occ=2;
			}	
		}
		else if(direction(nx,ny,screen)==4)
		{
			for(int i=1;i<=_x-nx;i++){
				if(screen[_y+i][_x-i]==11||screen[_y+i][_x-i]==12||screen[_y+i][_x-i]==13||screen[_y+i][_x-i]==14||screen[_y+i][_x-i]==15||screen[_y+i][_x-i]==16)	//si il y a une piece blanche sur le chemin 
					occ=1;
				else if ((screen[_y+i][_x-i]==1||screen[_y+i][_x-i]==2||screen[_y+i][_x-i]==3||screen[_y+i][_x-i]==4||screen[_y+i][_x-i]==5||screen[_y+i][_x-i]==6) && i!=_x-nx)
					occ=1;
				else if	((screen[_y+i][_x-i]==1||screen[_y+i][_x-i]==2||screen[_y+i][_x-i]==3||screen[_y+i][_x-i]==4||screen[_y+i][_x-i]==5||screen[_y+i][_x-i]==6) && i==_x-nx && occ==0)		//si la case d'arrivee est occupée par un pion noir
					occ=2;
			}	
		}
	}
	return occ;
}