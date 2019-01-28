#include "Cavalier.hh"

void Cavalier::deplacement(int nx, int ny, int **screen){
	screen[_y][_x]=0;
	
	if(_couleur==0)
		_val=3;
	else
		_val=13;

	_x=nx;
	_y=ny;
	screen[_y][_x]=_val;
}

bool Cavalier::allowed(int nx, int ny, int **screen){
	bool allowed=0;
	

	if(occupated(nx,ny,screen)==0 || occupated(nx,ny,screen)==2){
		if(abs(nx-_x)==2 && abs(ny-_y)==1)
			allowed=1;
		if(abs(nx-_x)==1 && abs(ny-_y)==2)
			allowed=1;
	}
	return allowed;
}

int Cavalier::direction(int nx, int ny, int **screen){
	if(nx-_x==-2 && ny-_y==-1)
		return 1;
	else if (nx-_x==-1 && ny-_y==-2)
		return 2;
	else if (ny-_y==-2 && nx-_x==1)
		return 3;
	else if (nx-_x==2 && ny-_y==-1)
		return 4;
	else if (nx-_x==-2 && ny-_y==1)
		return 5;
	else if (nx-_x==1 && ny-_y==2)
		return 6;
	else if(nx-_x==-1 && ny-_y==2)
		return 7;
	else 
		return 8;
}

int Cavalier::occupated(int nx, int ny, int **screen){
	int occ=0;

	if(_couleur==0){
			//si la case est occupée
		if(screen[ny][nx]==1||screen[ny][nx]==2||screen[ny][nx]==3||screen[ny][nx]==4||screen[ny][nx]==5||screen[ny][nx]==6)	//snx nxl y a une pnxece nonxre sur le chemnxn 
			occ=1;
		else if (screen[ny][nx]==11||screen[ny][nx]==12||screen[ny][nx]==13||screen[ny][nx]==14||screen[ny][nx]==15||screen[ny][nx]==16)
			occ=2;
	}
	else{
		if(screen[ny][nx]==11||screen[ny][nx]==12||screen[ny][nx]==13||screen[ny][nx]==14||screen[ny][nx]==15||screen[ny][nx]==16)	//snx nxl y a une pnxece blance sur le chemnxn 
			occ=1;
		else if (screen[ny][nx]==1||screen[ny][nx]==2||screen[ny][nx]==3||screen[ny][nx]==4||screen[ny][nx]==5||screen[ny][nx]==6)
			occ=2;
	}

	return occ;
}