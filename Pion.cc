#include "Pion.hh"

void Pion::deplacement(int nx, int ny, int **screen){
	screen[_y][_x]=0;
	
	if(_couleur==0)
		_val=1;
	else
		_val=11;

	_x=nx;
	_y=ny;
	screen[_y][_x]=_val;
}

bool Pion::allowed(int nx, int ny, int **screen){
	bool allowed;
	if(_couleur==0){
		if(first==0){ //Si c'est le premier coup
			if(nx-_x==0 && ny-_y==1  && occupated(nx,ny,screen)==0){	//si on avance d'une case et qu'elle n'est pas occupée
				allowed=1;
				first=1;
			}		

			else if(nx-_x==0 &&  ny-_y==2 && occupated(nx,ny,screen)==0 && occupated(nx,ny-1,screen)==0){ //si on avance de 2 cases et qu'elles ne sont pas occupées
				allowed=1;
				first=1;
			}

			else
				allowed=0;
		}
		else{
			if(nx-_x==0 && ny-_y==1  && occupated(nx,ny,screen)==0)		//si on avance d'une case et qu'elle n'est pas occupée
				allowed=1;

			else
				allowed=0;
		}

		if(nx-_x==1 && ny-_y==1 && occupated(nx,ny,screen)==2){  //si on capture un pion noir
			allowed=1;
			first=1;
		}	
				

		if(nx-_x==-1 && ny-_y==1 && occupated(nx,ny,screen)==2){	//si on capture un pion noir
			allowed=1;
			first=1;
		}	
	}
	else{
		if(first==0){ //Si c'est le premier coup
			if(nx-_x==0 && ny-_y==-1  && occupated(nx,ny,screen)==0){	//si on avance d'une case et qu'elle n'est pas occupée
				allowed=1;
				first=1;
			}		

			else if(nx-_x==0 &&  ny-_y==-2 && occupated(nx,ny,screen)==0 && occupated(nx,ny+1,screen)==0){ //si on avance de 2 cases et qu'elles ne sont pas occupées
				allowed=1;
				first=1;
			}

			else
				allowed=0;
		}
		else{
			if(nx-_x==0 && ny-_y==-1  && occupated(nx,ny,screen)==0)		//si on avance d'une case et qu'elle n'est pas occupée
				allowed=1;

			else
				allowed=0;
		}

		if(nx-_x==1 && ny-_y==-1 && occupated(nx,ny,screen)==2){  //si on capture un pion noir
			allowed=1;
			first=1;
		}	
				

		if(nx-_x==-1 && ny-_y==-1 && occupated(nx,ny,screen)==2){	//si on capture un pion noir
			allowed=1;
			first=1;
		}	
	}

	return allowed;
}

int Pion::occupated(int nx, int ny, int **screen){
	int occ;
	if(_couleur==0){
		if(screen[ny][nx]!=0){				//si la case est occupée
			if(screen[ny][nx]==1||screen[ny][nx]==2||screen[ny][nx]==3||screen[ny][nx]==4||screen[ny][nx]==5||screen[ny][nx]==6)	//si la case est occupée par un autre pion noir
				occ=1;
			else			//si la case est occupée par un pion blanc
				occ=2;
		}
		else{		//si la case n'est pas occupée
			occ=0;
		}
	}
	else{
		if(screen[ny][nx]!=0){
			if(screen[ny][nx]==11||screen[ny][nx]==12||screen[ny][nx]==13||screen[ny][nx]==14||screen[ny][nx]==15||screen[ny][nx]==16)
				occ=1;
			else
				occ=2;
		}

		else{
			occ=0;
		}
	}

	return occ;
}