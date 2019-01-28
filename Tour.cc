#include "Tour.hh"

void Tour::deplacement(int nx, int ny, int **screen){
	screen[_y][_x]=0;
	
	if(_couleur==0)
		_val=2;
	else
		_val=12;

	_x=nx;
	_y=ny;
	screen[_y][_x]=_val;
}

bool Tour::allowed(int nx, int ny, int **screen){
	bool allowed=0;
	
	if((occupated(nx,ny,screen)==0 || occupated(nx,ny,screen)==2) && (nx-_x==0 || ny-_y==0)){
		allowed=1;
	}

	return allowed;
}

int Tour::direction(int nx, int ny, int **screen){
	if(nx-_x<0)
		return 1;
	else if (ny-_y<0)
		return 2;
	else if (nx-_x>0)
		return 3;
	else
		return 4;
}

int Tour::occupated(int nx, int ny, int **screen){
	int occ=0;

	if(_couleur==0){
			//si la case est occupée
		if(direction(nx,ny,screen)==1)
		{
			for(int i=_x-1;i>=nx;i--){


				if(screen[ny][i]==1||screen[ny][i]==2||screen[ny][i]==3||screen[ny][i]==4||screen[ny][i]==5||screen[ny][i]==6)	//si il y a une piece noire sur le chemin 
					occ=1;
				else if ((screen[ny][i]==11||screen[ny][i]==12||screen[ny][i]==13||screen[ny][i]==14||screen[ny][i]==15||screen[ny][i]==16) && i!=nx)
					occ=1;
				else if	((screen[ny][i]==11||screen[ny][i]==12||screen[ny][i]==13||screen[ny][i]==14||screen[ny][i]==15||screen[ny][i]==16) && i==nx && occ==0)		//si la case d'arrivee est occupée par un pion blanc
					occ=2;
			}	
		}
		else if(direction(nx,ny,screen)==2)
		{
			for(int i=_y-1;i>=ny;i--){
				if(screen[i][nx]==1||screen[i][nx]==2||screen[i][nx]==3||screen[i][nx]==4||screen[i][nx]==5||screen[i][nx]==6)	//si il y a une piece noire sur le chemin 
					occ=1;
				else if ((screen[i][nx]==11||screen[i][nx]==12||screen[i][nx]==13||screen[i][nx]==14||screen[i][nx]==15||screen[i][nx]==16) && i!=ny)
					occ=1;
				else if	((screen[i][nx]==11||screen[i][nx]==12||screen[i][nx]==13||screen[i][nx]==14||screen[i][nx]==15||screen[i][nx]==16) && i==ny && occ==0)		//si la case d'arrivee est occupée par un pion blanc
					occ=2;
			}	
		}
		else if(direction(nx,ny,screen)==3)
		{
			for(int i=_x+1;i<=nx;i++){
				if(screen[ny][i]==1||screen[ny][i]==2||screen[ny][i]==3||screen[ny][i]==4||screen[ny][i]==5||screen[ny][i]==6)	//si il y a une piece noire sur le chemin 
					occ=1;
				else if ((screen[ny][i]==11||screen[ny][i]==12||screen[ny][i]==13||screen[ny][i]==14||screen[ny][i]==15||screen[ny][i]==16) && i!=nx)
					occ=1;
				else if	((screen[ny][i]==11||screen[ny][i]==12||screen[ny][i]==13||screen[ny][i]==14||screen[ny][i]==15||screen[ny][i]==16) && i==nx && occ==0)		//si la case d'arrivee est occupée par un pion blanc
					occ=2;
			}	
		}
		else if(direction(nx,ny,screen)==4)
		{
			for(int i=_y+1;i<=ny;i++){
				if(screen[i][nx]==1||screen[i][nx]==2||screen[i][nx]==3||screen[i][nx]==4||screen[i][nx]==5||screen[i][nx]==6)	//si il y a une piece noire sur le chemin 
					occ=1;
				else if ((screen[i][nx]==11||screen[i][nx]==12||screen[i][nx]==13||screen[i][nx]==41||screen[i][nx]==15||screen[i][nx]==16) && i!=ny)
					occ=1;
				else if	((screen[i][nx]==11||screen[i][nx]==12||screen[i][nx]==13||screen[i][nx]==41||screen[i][nx]==15||screen[i][nx]==16) && i==ny && occ==0)		//si la case d'arrivee est occupée par un pion blanc
					occ=2;
			}	
		}
	}
	else{
		if(direction(nx,ny,screen)==1)
		{
			for(int i=_x-1;i>=nx;i--){
				if(screen[ny][i]==11||screen[ny][i]==12||screen[ny][i]==13||screen[ny][i]==14||screen[ny][i]==15||screen[ny][i]==16)	//si il y a une piece blance sur le chemin 
					occ=1;
				else if ((screen[ny][i]==1||screen[ny][i]==2||screen[ny][i]==3||screen[ny][i]==4||screen[ny][i]==5||screen[ny][i]==6) && i!=nx)
					occ=1;
				else if	((screen[ny][i]==1||screen[ny][i]==2||screen[ny][i]==3||screen[ny][i]==4||screen[ny][i]==5||screen[ny][i]==6) && i==nx && occ==0)		//si la case d'arrivee est occupée par un pion noir
					occ=2;
			}	
		}
		else if(direction(nx,ny,screen)==2)
		{
			for(int i=_y-1;i>=ny;i--){
				if(screen[i][nx]==11||screen[i][nx]==12||screen[i][nx]==13||screen[i][nx]==14||screen[i][nx]==15||screen[i][nx]==16 )	//si il y a une piece blanche sur le chemin 
					occ=1;
				else if ((screen[i][nx]==1||screen[i][nx]==2||screen[i][nx]==3||screen[i][nx]==4||screen[i][nx]==5||screen[i][nx]==6) && i!=ny)
					occ=1;
				else if	((screen[i][nx]==1||screen[i][nx]==2||screen[i][nx]==3||screen[i][nx]==4||screen[i][nx]==5||screen[i][nx]==6) && i==ny && occ==0)		//si la case d'arrivee est occupée par un pion noir
					occ=2;
			}	
		}
		else if(direction(nx,ny,screen)==3)
		{
			for(int i=_x+1;i<=nx;i++){
				if(screen[ny][i]==11||screen[ny][i]==12||screen[ny][i]==13||screen[ny][i]==14||screen[ny][i]==15||screen[ny][i]==16)	//si il y a une piece blanche sur le chemin 
					occ=1;
				else if ((screen[ny][i]==1||screen[ny][i]==2||screen[ny][i]==3||screen[ny][i]==4||screen[ny][i]==5||screen[ny][i]==6) && i!=nx)
					occ=1;
				else if	((screen[ny][i]==1||screen[ny][i]==2||screen[ny][i]==3||screen[ny][i]==4||screen[ny][i]==5||screen[ny][i]==6) && i==nx && occ==0)		//si la case d'arrivee est occupée par un pion noir
					occ=2;
			}	
		}
		else if(direction(nx,ny,screen)==4)
		{
			for(int i=_y+1;i<=ny;i++){
				if(screen[i][nx]==11||screen[i][nx]==12||screen[i][nx]==13||screen[i][nx]==14||screen[i][nx]==15||screen[i][nx]==16)	//si il y a une piece blanche sur le chemin 
					occ=1;
				else if ((screen[i][nx]==1||screen[i][nx]==2||screen[i][nx]==3||screen[i][nx]==4||screen[i][nx]==5||screen[i][nx]==6) && i!=ny)
					occ=1;
				else if	((screen[i][nx]==1||screen[i][nx]==2||screen[i][nx]==3||screen[i][nx]==4||screen[i][nx]==5||screen[i][nx]==6) && i==ny && occ==0)		//si la case d'arrivee est occupée par un pion noir
					occ=2;
			}	
		}
	}
	return occ;
}