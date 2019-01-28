#include "Roi.hh"

void Roi::deplacement(int nx, int ny, int **screen){
	screen[_y][_x]=0;
	
	if(_couleur==0)
		_val=6;
	else
		_val=16;

	_x=nx;
	_y=ny;
	screen[_y][_x]=_val;
}

bool Roi::allowed(int nx, int ny, int **screen){
	bool allowed=0;
	
	if(occupated(nx,ny,screen)==0 || occupated(nx,ny,screen)==2){
		if(abs(nx-_x)==1 && abs(ny-_y)==abs(nx-_x))
			allowed=1;
		if((nx-_x==0 && abs(ny-_y)==1) || (ny-_y==0 && abs(nx-_x)==1))
			allowed=1;
	}

	return allowed;
}

int Roi::occupated(int nx, int ny, int **screen){
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