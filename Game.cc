#include "Game.hh"

/*Déclaration de classes*/
Map* carte;

/*SDL*/
SDL_Renderer* Game::renderer ;	
SDL_Event Game::event;
SDL_Texture* tex;

/*SDL_TTF*/
SDL_Surface *Game::text;
SDL_Rect Game::destText;
TTF_Font *Game::police;


//////////////////*Constructeur*//////////////////

Game::Game(const char* title, int x, int y, int width, int height){
	_width = width;
	_height = height;

	if(SDL_Init(SDL_INIT_EVERYTHING)==0){	

		window = SDL_CreateWindow(title, x, y, width, height,0);	

		renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_TARGETTEXTURE);
		//SDL_SetRenderDrawColor(renderer,255,255,255,255);			//Permet de définir la couleur par défaut de la fenêtre graphique
			
		isRunning = true;
	}
	else{

		isRunning = false;
	}


	screen = new int*[8];
	for(int i=0;i<8;i++){
		screen[i] = new int[8];
	}


	for(int i=0;i<16;i++){
		if(i<8)
			listePiece.push_back(new Pion(i,1,0));
		else
			listePiece.push_back(new Pion(i-8,6,1));
	}

	listePiece.push_back(new Tour(0,0,0));
	listePiece.push_back(new Tour(7,0,0));
	listePiece.push_back(new Tour(0,7,1));
	listePiece.push_back(new Tour(7,7,1));

	listePiece.push_back(new Cavalier(1,0,0));
	listePiece.push_back(new Cavalier(6,0,0));
	listePiece.push_back(new Cavalier(1,7,1));
	listePiece.push_back(new Cavalier(6,7,1));

	listePiece.push_back(new Fou(2,0,0));
	listePiece.push_back(new Fou(5,0,0));
	listePiece.push_back(new Fou(2,7,1));
	listePiece.push_back(new Fou(5,7,1));
	
	listePiece.push_back(new Reine(3,0,0));
	listePiece.push_back(new Reine(3,7,1));

	listePiece.push_back(new Roi(4,0,0));
	listePiece.push_back(new Roi(4,7,1));
		
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if((i==0 || i==7) && j==0)
				screen[j][i]=2;
			else if((i==1 || i==6) && j==0)
				screen[j][i]=3;
			else if((i==2 || i==5) && j==0)
				screen[j][i]=4;
			else if(i==3 && j==0)
				screen[j][i]=5;
			else if(i==4 && j==0)
				screen[j][i]=6;
			else if(j==1)
				screen[j][i]=1;
			else if((i==0 || i==7) && j==7)
				screen[j][i]=12;
			else if((i==1 || i==6) && j==7)
				screen[j][i]=13;
			else if((i==2 || i==5) && j==7)
				screen[j][i]=14;
			else if(i==3 && j==7)
				screen[j][i]=15;
			else if(i==4 && j==7)
				screen[j][i]=16;
			else if(j==6)
				screen[j][i]=11;
			else
				screen[j][i] = 0;

		}
	}

	src.x = src.y = src.w = src.h =0;
	dest.w=dest.h=80;

	roiN = TextureManager::LoadTexture("Images/RoN.png");
	reineN = TextureManager::LoadTexture("Images/ReN.png");
	fouN = TextureManager::LoadTexture("Images/FN.png");
	tourN = TextureManager::LoadTexture("Images/TN.png");
	pionN = TextureManager::LoadTexture("Images/PN.png");
	cavN = TextureManager::LoadTexture("Images/CN.png");
	roiB = TextureManager::LoadTexture("Images/RoB.png");
	reineB = TextureManager::LoadTexture("Images/ReB.png");
	fouB = TextureManager::LoadTexture("Images/FB.png");
	tourB = TextureManager::LoadTexture("Images/TB.png");
	pionB = TextureManager::LoadTexture("Images/PB.png");
	cavB = TextureManager::LoadTexture("Images/CB.png");
	
	select=0;
	iter=0;
	winner=0;

	carte = new Map();

	TTF_Init();
	police = TTF_OpenFont("Police/stocky.ttf", 65);
	destText = {15,15,200,20};
	fichierc= "Tour : White";
	text = TTF_RenderText_Blended(police,fichierc, {255, 255, 255});
	tex = SDL_CreateTextureFromSurface(renderer,text);

	tour = 2;
}


//////////////////*Destructeur*//////////////////

Game::~Game(){
	for(int i=0;i<8;i++){
		delete[] screen[i];
	}
	
	delete[] screen;

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

//////////////////*Fonctions Membres*//////////////////


/*Met àjour isRunning si on quitte le jeu*/
void Game::handleEvent(){
	SDL_PollEvent(&event);
	switch(event.type){
		case SDL_QUIT:
			isRunning = false;
			break;

		default:
			break; 
	}
}

bool Game::echec(Piece *roi, int x, int y, int nx, int ny, int val,int **screen){
	bool echec=0;

	int ** screentemp;
	screentemp = new int*[8];
	for(int i=0;i<8;i++){
		screentemp[i] = new int[8];
	}

	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			screentemp[i][j]=screen[i][j];
		}
	}

	Piece *roitemp;

	if(roi->getVal()==val){
		screentemp[roi->getY()][roi->getX()]=0;
		screentemp[ny][nx]=val;
		if(roi->getCouleur()==1)
			roitemp = new Roi(nx,ny,1);
		else
			roitemp = new Roi(nx,ny,0);
	}
	else{
		if(roi->getCouleur()==1)
			roitemp = new Roi(roi->getX(),roi->getY(),1);
		else
			roitemp = new Roi(roi->getX(),roi->getY(),0);
		screentemp[y][x]=0;
		screentemp[ny][nx]=val;
	}

	

	if(roitemp->getCouleur()==1){
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				if(screentemp[i][j]==1){
					if((roitemp->getX()==j-1 && roitemp->getY()==i+1) || (roitemp->getX()==j+1 && roitemp->getY()==i+1))
						echec = 1;
				}
				else if(screentemp[i][j]==2){
					
					if(roitemp->getX()==j){
						for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
							if((*it1)->getX()==j && (*it1)->getY()==i){
								if((*it1)->occupated(roitemp->getX(),roitemp->getY(),screentemp)==2)
									echec=1;
								break;
							}
						}
					}
					if(roitemp->getY()==i){
						for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
							if((*it1)->getX()==j && (*it1)->getY()==i){
								if((*it1)->occupated(roitemp->getX(),roitemp->getY(),screentemp)==2)
									echec=1;
								break;
							}
						}
					}
					
				}
				else if(screentemp[i][j]==3){
					
					if((roitemp->getX()==j-1 && roitemp->getY()==i+2) || (roitemp->getX()==j+1 && roitemp->getY()==i+2) || (roitemp->getX()==j-1 && roitemp->getY()==i-2) || (roitemp->getX()==j+1 && roitemp->getY()==i-2))
						echec=1;

					if((roitemp->getX()==j+2 && roitemp->getY()==i+1)|| (roitemp->getX()==j+2 && roitemp->getY()==i-1)|| (roitemp->getX()==j-2 && roitemp->getY()==i+1)|| (roitemp->getX()==j-2 && roitemp->getY()==i-1))
						echec=1;
					
				}
				else if(screentemp[i][j]==4){
					
					if(abs(roitemp->getX()-j)==abs(roitemp->getY()-i)){
						for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
							if((*it1)->getX()==j && (*it1)->getY()==i){
								if((*it1)->occupated(roitemp->getX(),roitemp->getY(),screentemp)==2)
									echec=1;
								break;
							}
						}
					}
				}
				else if(screentemp[i][j]==5){
					
					if(roitemp->getX()==j){
						for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
							if((*it1)->getX()==i && (*it1)->getY()==j){
								if((*it1)->occupated(roitemp->getX(),roitemp->getY(),screentemp)==2)
									echec=1;
								break;
							}
						}
					}
					if(roitemp->getY()==i){
						for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
							if((*it1)->getX()==j && (*it1)->getY()==i){
								if((*it1)->occupated(roitemp->getX(),roitemp->getY(),screentemp)==2)
									echec=1;
								break;
							}
						}
					}
					if(abs(roitemp->getX()-j)==abs(roitemp->getY()-i)){
						for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
							if((*it1)->getX()==j && (*it1)->getY()==i){
								if((*it1)->occupated(roitemp->getX(),roitemp->getY(),screentemp)==2)
									echec=1;
								break;
							}
						}
					}
				}
				else if(screentemp[i][j]==6){
					
					if((roitemp->getX()==j-1 && roitemp->getY()==i+1) || (roitemp->getX()==j+1 && roitemp->getY()==i+1) || (roitemp->getX()==j-1 && roitemp->getY()==i-1) || (roitemp->getX()==j+1 && roitemp->getY()==i-1))
						echec=1;

					if((roitemp->getX()==j+1 && roitemp->getY()==0)|| (roitemp->getX()==j+1 && roitemp->getY()==0)|| (roitemp->getX()==0 && roitemp->getY()==i+1)|| (roitemp->getX()==0 && roitemp->getY()==i-1))
						echec=1;

				}
			}
		}
	}
	else{
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				if(screentemp[i][j]==11){
					
					if((roitemp->getX()==j-1 && roitemp->getY()==i-1) || (roitemp->getX()==j+1 && roitemp->getY()==i-1))
						echec = 1;
				}
				else if(screentemp[i][j]==12){
					
					if(roitemp->getX()==j){
						for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
							if((*it1)->getX()==j && (*it1)->getY()==i){
								if((*it1)->occupated(roitemp->getX(),roitemp->getY(),screentemp)==2)
									echec=1;
								break;
							}
						}
					}
					if(roitemp->getY()==i){
						for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
							if((*it1)->getX()==j && (*it1)->getY()==i){
								if((*it1)->occupated(roitemp->getX(),roitemp->getY(),screentemp)==2)
									echec=1;
								break;
							}
						}
					}
					
				}
				else if(screentemp[i][j]==13){
					
					if((roitemp->getX()==j-1 && roitemp->getY()==i+2) || (roitemp->getX()==j+1 && roitemp->getY()==i+2) || (roitemp->getX()==j-1 && roitemp->getY()==i-2) || (roitemp->getY()==j+1 && roitemp->getY()==i-2))
						echec=1;

					if((roitemp->getX()==j+2 && roitemp->getY()==i+1)|| (roitemp->getX()==j+2 && roitemp->getY()==i-1)|| (roitemp->getX()==j-2 && roitemp->getY()==i+1)|| (roitemp->getX()==j-2 && roitemp->getY()==i-1))
						echec=1;
				}
				else if(screentemp[i][j]==14){
					
					if(abs(roitemp->getX()-j)==abs(roitemp->getY()-i)){
						for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
							if((*it1)->getX()==j && (*it1)->getY()==i){
								if((*it1)->occupated(roitemp->getX(),roitemp->getY(),screentemp)==2)
									echec=1;
								break;
							}
						}
					}
				}
				else if(screentemp[i][j]==15){
					
					if(roitemp->getX()==j){
						for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
							if((*it1)->getX()==j && (*it1)->getY()==i){
								if((*it1)->occupated(roitemp->getX(),roitemp->getY(),screentemp)==2)
									echec=1;
								break;
							}
						}
					}
					if(roitemp->getY()==i){
						for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
							if((*it1)->getX()==j && (*it1)->getY()==i){
								if((*it1)->occupated(roitemp->getX(),roitemp->getY(),screentemp)==2)
									echec=1;
								break;
							}
						}
					}
					if(abs(roitemp->getX()-j)==abs(roitemp->getY()-i)){
						for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
							if((*it1)->getX()==j && (*it1)->getY()==i){
								if((*it1)->occupated(roitemp->getX(),roitemp->getY(),screentemp)==2)
									echec=1;
								break;
							}
						}
					}
				}
				else if(screentemp[i][j]==16){
					
					if((roitemp->getX()==j-1 && roitemp->getY()==i+1) || (roitemp->getX()==j+1 && roitemp->getY()==i+1) || (roitemp->getX()==j-1 && roitemp->getY()==i-1) || (roitemp->getX()==j+1 && roitemp->getY()==i-1))
						echec=1;

					if((roitemp->getX()==j+1 && roitemp->getY()==0)|| (roitemp->getX()==j+1 && roitemp->getY()==0)|| (roitemp->getX()==0 && roitemp->getY()==i+1)|| (roitemp->getX()==0 && roitemp->getY()==i-1))
						echec=1;

					
				}
			}
		}
	}

	for(int i=0;i<8;i++){
		delete[] screentemp[i];
	}
	
	delete[] screentemp;

	return echec;
}

bool Game::echec2(Piece *roi, int nx, int ny, int val){
	bool echec=0;
	Piece *roitemp;

	int ** screentemp;
	screentemp = new int*[8];


	for(int i=0;i<8;i++){
		screentemp[i] = new int[8];
	}

	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			screentemp[i][j]=screen[i][j];
		}
	}
	
	


	if(roi->getCouleur()==1){
		if(roi->getVal()==val){
			screentemp[roi->getY()][roi->getX()]=0;
			screentemp[ny][nx]=val;
			roitemp = new Roi(nx,ny,1);
		}
		else{
			roitemp = new Roi(roi->getX(),roi->getY(),1);
		}
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				if(screentemp[i][j]<=16 && screentemp[i][j]>=11){
					for(list <Piece *>::iterator it = listePiece.begin(); it != listePiece.end(); it ++){
						if((*it)->getX()==j && (*it)->getY()==i){
							if((*this).echec(roitemp,(*it)->getX(),(*it)->getY(),(*it)->getX(),(*it)->getY(),(*it)->getVal(),screentemp)==1){
								echec=1;
							}
						}
					}
				}
			}
		}
	}
	else{
		if(roi->getVal()==val){
			screentemp[roi->getY()][roi->getX()]=0;
			screentemp[ny][nx]=val;
			roitemp = new Roi(nx,ny,0);
		}
		else{
			roitemp = new Roi(roi->getX(),roi->getY(),0);
		}
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				if(screentemp[i][j]<=6 && screentemp[i][j]>=1){
					for(list <Piece *>::iterator it = listePiece.begin(); it != listePiece.end(); it ++){
						if((*it)->getX()==j && (*it)->getY()==i){
							if((*this).echec(roitemp,(*it)->getX(),(*it)->getY(),(*it)->getX(),(*it)->getY(),(*it)->getVal(),screentemp)==1){
								echec=1;
							}
						}
					}
				}
			}
		}
	}


	for(int i=0;i<8;i++){
		delete[] screentemp[i];
	}
	
	delete[] screentemp;

	return echec;
}


bool Game::echecmat(Piece *roi){
	bool echecmat=0;

	
		if(roi->getX()==0){
			if(roi->getY()==0){
				if((*this).echec2(roi,roi->getX(),roi->getY(),roi->getVal())==1 ){
					if((*this).echec2(roi,roi->getX(),roi->getY()+1,roi->getVal())==1 || roi->allowed(roi->getX(),roi->getY()+1,screen)==0){
						if((*this).echec2(roi,roi->getX()+1,roi->getY(),roi->getVal())==1 || roi->allowed(roi->getX()+1,roi->getY(),screen)==0){
							if((*this).echec2(roi,roi->getX()+1,roi->getY()+1,roi->getVal())==1 || roi->allowed(roi->getX()+1,roi->getY()+1,screen)==0){
								echecmat=1;
							}
						}
					}
				}
			}
			else if(roi->getY()==7){
				if((*this).echec2(roi,roi->getX(),roi->getY(),roi->getVal())==1 ){
					if((*this).echec2(roi,roi->getX(),roi->getY()-1,roi->getVal())==1|| roi->allowed(roi->getX(),roi->getY()-1,screen)==0){
						if((*this).echec2(roi,roi->getX()+1,roi->getY(),roi->getVal())==1|| roi->allowed(roi->getX()+1,roi->getY(),screen)==0){
							if((*this).echec2(roi,roi->getX()+1,roi->getY()-1,roi->getVal())==1|| roi->allowed(roi->getX()+1,roi->getY()-1,screen)==0){
								echecmat=1;
							}
						}
					}
				}
			}
			else{
				if((*this).echec2(roi,roi->getX(),roi->getY(),roi->getVal())==1){
					if((*this).echec2(roi,roi->getX(),roi->getY()+1,roi->getVal())==1|| roi->allowed(roi->getX(),roi->getY()+1,screen)==0){
						if((*this).echec2(roi,roi->getX(),roi->getY()-1,roi->getVal())==1|| roi->allowed(roi->getX(),roi->getY()-1,screen)==0){
							if((*this).echec2(roi,roi->getX()+1,roi->getY()+1,roi->getVal())==1|| roi->allowed(roi->getX()+1,roi->getY()+1,screen)==0){
								if((*this).echec2(roi,roi->getX()+1,roi->getY()-1,roi->getVal())==1|| roi->allowed(roi->getX()+1,roi->getY()-1,screen)==0){
									if((*this).echec2(roi,roi->getX()+1,roi->getY(),roi->getVal())==1|| roi->allowed(roi->getX()+1,roi->getY(),screen)==0){
										echecmat=1;
									}
								}
							}
						}
					}
				}
			}
		}
		else if(roi->getY()==0){
			if(roi->getX()==7){
				if((*this).echec2(roi,roi->getX(),roi->getY(),roi->getVal())==1 ){
					if((*this).echec2(roi,roi->getX(),roi->getY()+1,roi->getVal())==1|| roi->allowed(roi->getX(),roi->getY()+1,screen)==0){
						if((*this).echec2(roi,roi->getX()-1,roi->getY(),roi->getVal())==1|| roi->allowed(roi->getX()-1,roi->getY(),screen)==0){
							if((*this).echec2(roi,roi->getX()-1,roi->getY()+1,roi->getVal())==1|| roi->allowed(roi->getX()-1,roi->getY()+1,screen)==0){
								echecmat=1;
							}
						}
					}
				}
			}
			else{
				if((*this).echec2(roi,roi->getX(),roi->getY(),roi->getVal())==1){
					if((*this).echec2(roi,roi->getX()+1,roi->getY(),roi->getVal())==1|| roi->allowed(roi->getX()+1,roi->getY(),screen)==0){
						if((*this).echec2(roi,roi->getX()+1,roi->getY()+1,roi->getVal())==1|| roi->allowed(roi->getX()+1,roi->getY()+1,screen)==0){
							if((*this).echec2(roi,roi->getX(),roi->getY()+1,roi->getVal())==1|| roi->allowed(roi->getX(),roi->getY()+1,screen)==0){
								if((*this).echec2(roi,roi->getX()-1,roi->getY()+1,roi->getVal())==1|| roi->allowed(roi->getX()-1,roi->getY()+1,screen)==0){
									if((*this).echec2(roi,roi->getX()-1,roi->getY(),roi->getVal())==1|| roi->allowed(roi->getX()-1,roi->getY(),screen)==0){
										echecmat=1;
									}
								}
							}
						}
					}
				}
			}
		}
		else if(roi->getX()==7){
			if(roi->getY()==7){
				if((*this).echec2(roi,roi->getX(),roi->getY(),roi->getVal())==1){
					if((*this).echec2(roi,roi->getX(),roi->getY()-1,roi->getVal())==1|| roi->allowed(roi->getX(),roi->getY()-1,screen)==0){
						if((*this).echec2(roi,roi->getX()-1,roi->getY(),roi->getVal())==1|| roi->allowed(roi->getX()-1,roi->getY(),screen)){
							if((*this).echec2(roi,roi->getX()-1,roi->getY()-1,roi->getVal())==1|| roi->allowed(roi->getX()-1,roi->getY()-1,screen)==0){
								echecmat=1;
							}
						}
					}
				}
			}
			else{
				if((*this).echec2(roi,roi->getX(),roi->getY(),roi->getVal())==1 ){
					if((*this).echec2(roi,roi->getX(),roi->getY()-1,roi->getVal())==1|| roi->allowed(roi->getX(),roi->getY()-1,screen)==0){
						if((*this).echec2(roi,roi->getX()-1,roi->getY()-1,roi->getVal())==1|| roi->allowed(roi->getX()-1,roi->getY()-1,screen)==0){
							if((*this).echec2(roi,roi->getX()-1,roi->getY(),roi->getVal())==1|| roi->allowed(roi->getX()-1,roi->getY(),screen)==0){
								if((*this).echec2(roi,roi->getX()-1,roi->getY()+1,roi->getVal())==1|| roi->allowed(roi->getX()-1,roi->getY()+1,screen)==0){
									if((*this).echec2(roi,roi->getX(),roi->getY()+1,roi->getVal())==1|| roi->allowed(roi->getX(),roi->getY()+1,screen)==0){
										echecmat=1;
									}
								}
							}
						}
					}
				}
			}
		}
		else if(roi->getY()==7){
			if((*this).echec2(roi,roi->getX(),roi->getY(),roi->getVal())==1 ){
				if((*this).echec2(roi,roi->getX()-1,roi->getY(),roi->getVal())==1|| roi->allowed(roi->getX()-1,roi->getY(),screen)==0){
					if((*this).echec2(roi,roi->getX()-1,roi->getY()-1,roi->getVal())==1|| roi->allowed(roi->getX()-1,roi->getY()-1,screen)==0){
						if((*this).echec2(roi,roi->getX(),roi->getY()-1,roi->getVal())==1|| roi->allowed(roi->getX(),roi->getY()-1,screen)==0){
							if((*this).echec2(roi,roi->getX()+1,roi->getY()-1,roi->getVal())==1|| roi->allowed(roi->getX()+1,roi->getY()-1,screen)==0){
								if((*this).echec2(roi,roi->getX()+1,roi->getY(),roi->getVal())==1|| roi->allowed(roi->getX()+1,roi->getY(),screen)==0){
									echecmat=1;
								}
							}
						}
					}
				}
			}
		}
		else{
			if((*this).echec2(roi,roi->getX(),roi->getY(),roi->getVal())==1){
				if((*this).echec2(roi,roi->getX()-1,roi->getY()-1,roi->getVal())==1|| roi->allowed(roi->getX()-1,roi->getY()-1,screen)==0){
					if((*this).echec2(roi,roi->getX(),roi->getY()-1,roi->getVal())==1|| roi->allowed(roi->getX(),roi->getY()-1,screen)==0){
						if((*this).echec2(roi,roi->getX()+1,roi->getY()-1,roi->getVal())==1|| roi->allowed(roi->getX()+1,roi->getY()-1,screen)==0){
							if((*this).echec2(roi,roi->getX()+1,roi->getY(),roi->getVal())==1|| roi->allowed(roi->getX()+1,roi->getY(),screen)==0){
								if((*this).echec2(roi,roi->getX()+1,roi->getY()+1,roi->getVal())==1|| roi->allowed(roi->getX()+1,roi->getY()+1,screen)==0){
									if((*this).echec2(roi,roi->getX(),roi->getY()+1,roi->getVal())==1|| roi->allowed(roi->getX(),roi->getY()+1,screen)==0){
										if((*this).echec2(roi,roi->getX()-1,roi->getY()+1,roi->getVal())==1|| roi->allowed(roi->getX()-1,roi->getY()+1,screen)==0){
											if((*this).echec2(roi,roi->getX()-1,roi->getY(),roi->getVal())==1|| roi->allowed(roi->getX()-1,roi->getY(),screen)==0){
												echecmat=1;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	

	return echecmat;
		
}

bool Game::save(Piece *roi){
	int save=0,x,y;

	if(roi->getCouleur()==1){
		for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
			if((*it1)->allowed(roi->getX(),roi->getY(),screen)==1 && (*it1)->getCouleur()==0){
				x=(*it1)->getX();
				y=(*it1)->getY();
				break;
			}
		}

		for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
			if((*it1)->allowed(x,y,screen)==1 && (*it1)->getVal()!=roi->getVal() && (*it1)->getCouleur()==1){
				save=1;
				break;
			}
		}
	}
	else{
		for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
			if((*it1)->allowed(roi->getX(),roi->getY(),screen)==1 && (*it1)->getCouleur()==1){
				x=(*it1)->getX();
				y=(*it1)->getY();
				break;
			}
		}

		for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
			if((*it1)->allowed(x,y,screen)==1 && (*it1)->getVal()!=roi->getVal() && (*it1)->getCouleur()==0){
				save=1;
				break;
			}
		}
	}

	
	return save;
}

bool Game::save2(Piece *roi){
	int save=0,x,y;
	bool a=0;

	if(roi->getCouleur()==1){
		for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
			if((*it1)->allowed(roi->getX(),roi->getY(),screen)==1 && (*it1)->getCouleur()==0){
				x=(*it1)->getX();
				y=(*it1)->getY();
				a=1;
				break;
			}
		}

		if(a){
			if(x==roi->getX()){
				if(x-roi->getX()<0){
					for(int i=1;i<abs(x-roi->getX());i++){
						for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
							if((*it1)->allowed(x+i,y,screen)==1 && (*it1)->getVal()!=roi->getVal() && (*it1)->getCouleur()==1){
								save=1;
								break;
							}
						}
					}
				}
				else{
					for(int i=1;i<abs(x-roi->getX());i++){
						for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
							if((*it1)->allowed(x-i,y,screen)==1 && (*it1)->getVal()!=roi->getVal() && (*it1)->getCouleur()==1){
								save=1;
								break;
							}
						}
					}
				}
			}

			else if(y==roi->getY()){
				if(y-roi->getY()<0){
					for(int i=1;i<abs(x-roi->getX());i++){
						for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
							if((*it1)->allowed(x,y+i,screen)==1 && (*it1)->getVal()!=roi->getVal() && (*it1)->getCouleur()==1){
								save=1;
								break;
							}
						}
					}
				}
				else{
					for(int i=1;i<abs(x-roi->getX());i++){
						for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
							if((*it1)->allowed(x,y-i,screen)==1 && (*it1)->getVal()!=roi->getVal() && (*it1)->getCouleur()==1){
								save=1;
								break;
							}
						}
					}
				}
			}

			else{
				if(y-roi->getY()<0 && x-roi->getX()<0){
					for(int i=1;i<abs(x-roi->getX());i++){
						for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
							if((*it1)->allowed(x+i,y+i,screen)==1 && (*it1)->getVal()!=roi->getVal() && (*it1)->getCouleur()==1){
								save=1;
								break;
							}
						}
					}
				}
				else if(y-roi->getY()<0 && x-roi->getX()>0){
					for(int i=1;i<abs(x-roi->getX());i++){
						for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
							if((*it1)->allowed(x-i,y+i,screen)==1 && (*it1)->getVal()!=roi->getVal() && (*it1)->getCouleur()==1){
								save=1;
								break;
							}
						}
					}
				}
				else if(y-roi->getY()>0 && x-roi->getX()<0){
					for(int i=1;i<abs(x-roi->getX());i++){
						for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
							if((*it1)->allowed(x-i,y+i,screen)==1 && (*it1)->getVal()!=roi->getVal() && (*it1)->getCouleur()==1){
								save=1;
								break;
							}
						}
					}
				}
				else{
					for(int i=1;i<abs(x-roi->getX());i++){
						for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
							if((*it1)->allowed(x-i,y-i,screen)==1 && (*it1)->getVal()!=roi->getVal() && (*it1)->getCouleur()==1){
								save=1;
								break;
							}
						}
					}
				}
			}
		}
	}
	else{
		for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
			if((*it1)->allowed(roi->getX(),roi->getY(),screen)==1 && (*it1)->getCouleur()==1){
				x=(*it1)->getX();
				y=(*it1)->getY();
				a=1;
				break;
			}
		}

		if(a){
			if(x==roi->getX()){
				if(x-roi->getX()<0){
					for(int i=1;i<abs(x-roi->getX());i++){
						for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
							if((*it1)->allowed(x+i,y,screen)==1 && (*it1)->getVal()!=roi->getVal() && (*it1)->getCouleur()==0){
								save=1;
								break;
							}
						}
					}
				}
				else{
					for(int i=1;i<abs(x-roi->getX());i++){
						for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
							if((*it1)->allowed(x-i,y,screen)==1 && (*it1)->getVal()!=roi->getVal() && (*it1)->getCouleur()==0){
								save=1;
								break;
							}
						}
					}
				}
			}

			else if(y==roi->getY()){
				if(y-roi->getY()<0){
					for(int i=1;i<abs(x-roi->getX());i++){
						for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
							if((*it1)->allowed(x,y+i,screen)==1 && (*it1)->getVal()!=roi->getVal() && (*it1)->getCouleur()==0){
								save=1;
								break;
							}
						}
					}
				}
				else{
					for(int i=1;i<abs(x-roi->getX());i++){
						for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
							if((*it1)->allowed(x,y-i,screen)==1 && (*it1)->getVal()!=roi->getVal() && (*it1)->getCouleur()==0){
								save=1;
								break;
							}
						}
					}
				}
			}

			else{
				if(y-roi->getY()<0 && x-roi->getX()<0){
					for(int i=1;i<abs(x-roi->getX());i++){
						for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
							if((*it1)->allowed(x+i,y+i,screen)==1 && (*it1)->getVal()!=roi->getVal() && (*it1)->getCouleur()==0){
								save=1;
								break;
							}
						}
					}
				}
				else if(y-roi->getY()<0 && x-roi->getX()>0){
					for(int i=1;i<abs(x-roi->getX());i++){
						for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
							if((*it1)->allowed(x-i,y+i,screen)==1 && (*it1)->getVal()!=roi->getVal() && (*it1)->getCouleur()==0){
								save=1;
								break;
							}
						}
					}
				}
				else if(y-roi->getY()>0 && x-roi->getX()<0){
					for(int i=1;i<abs(x-roi->getX());i++){
						for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
							if((*it1)->allowed(x-i,y+i,screen)==1 && (*it1)->getVal()!=roi->getVal() && (*it1)->getCouleur()==0){
								save=1;
								break;
							}
						}
					}
				}
				else{
					for(int i=1;i<abs(x-roi->getX());i++){
						for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
							if((*it1)->allowed(x-i,y-i,screen)==1 && (*it1)->getVal()!=roi->getVal() && (*it1)->getCouleur()==0){
								save=1;
								break;
							}
						}
					}
				}
			}
		}
	}

	
	return save;
}

/*Met à jour le jeu*/
void Game::update(){
	if(winner==0){
		if(iter>5){
			if(Game::event.type == SDL_MOUSEBUTTONDOWN){
				if(event.button.x>0 && event.button.x<640 && event.button.y<690 && event.button.y>50){
					if(!select){
						cout << "Sélection d'une pièce" << endl;
						y=(event.button.y-50)/80;
						x=event.button.x/80;
						select=1;
					}
					else{
						cout << "Mouvement d'une pièce" << endl;
						ny=(event.button.y-50)/80;
						nx=event.button.x/80;
						
						if(tour==1){
							if(screen[y][x]==1 || screen[y][x]==2 || screen[y][x]==3 || screen[y][x]==4 || screen[y][x]==5 || screen[y][x]==6){
								for(list <Piece *>::iterator it = listePiece.begin(); it != listePiece.end(); it ++){
									if((*it)->getX()==x && (*it)->getY()==y){

										if((*it)->allowed(nx,ny,screen) && (nx!=(*it)->getX() || ny!=(*it)->getY())){
											for(list <Piece *>::iterator it2 = listePiece.begin(); it2 != listePiece.end(); it2 ++){
												if((*it2)->getVal()==6){
													cout << "Echec1 = " << (*this).echec((*it2),(*it)->getX(),(*it)->getY(),nx,ny,(*it)->getVal(),screen) << endl;
													cout << "Echec2 = " << (*this).echec2((*it2),nx,ny,(*it)->getVal()) << endl;
													if((*this).echec((*it2),(*it)->getX(),(*it)->getY(),nx,ny,(*it)->getVal(),screen)==0 || (*this).echec2((*it2),nx,ny,(*it)->getVal())==0){
														for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
															if((*it1)->getX()==nx && (*it1)->getY()==ny){
																listePiece.remove(*it1);
																break;
															}
														}
														(*it)->deplacement(nx,ny,screen);
														fichierc= "Turn : White";
														SDL_FreeSurface(text);
														text = TTF_RenderText_Blended(police,fichierc, {255, 255, 255});
														tex = SDL_CreateTextureFromSurface(renderer,text);
														tour=2;
														break;
													}
													
												}
											}		
										}	
										break;
									}

								}
							}
						}
						else{
							if(screen[y][x]==11 || screen[y][x]==12 || screen[y][x]==13 || screen[y][x]==14 || screen[y][x]==15 || screen[y][x]==16){
								for(list <Piece *>::iterator it = listePiece.begin(); it != listePiece.end(); it ++){
									if((*it)->getX()==x && (*it)->getY()==y){

										if((*it)->allowed(nx,ny,screen) && (nx!=(*it)->getX() || ny!=(*it)->getY())){
											for(list <Piece *>::iterator it2 = listePiece.begin(); it2 != listePiece.end(); it2 ++){
												if((*it2)->getVal()==16){
													cout << "Echec1 = " << (*this).echec((*it2),(*it)->getX(),(*it)->getY(),nx,ny,(*it)->getVal(),screen) << endl;
													cout << "Echec2 = " << (*this).echec2((*it2),nx,ny,(*it)->getVal()) << endl;
													if((*this).echec((*it2),(*it)->getX(),(*it)->getY(),nx,ny,(*it)->getVal(),screen)==0 || (*this).echec2((*it2),nx,ny,(*it)->getVal())==0){
														for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
															if((*it1)->getX()==nx && (*it1)->getY()==ny){
																listePiece.remove(*it1);
																break;
															}
														}
														(*it)->deplacement(nx,ny,screen);
														
														fichierc= "Turn : Black";
														SDL_FreeSurface(text);
														text = TTF_RenderText_Blended(police,fichierc, {255, 255, 255});
														tex = SDL_CreateTextureFromSurface(renderer,text);
														tour=1;
														break;
													}
												}
											}
										}
										break;	
									}
								}
							}
						}
						select=0;
					}
				}
				iter=0;
			}	
			
		}
		iter++;

		for(list <Piece *>::iterator it1 = listePiece.begin(); it1 != listePiece.end(); it1 ++){
			if(((*it1)->getVal()==6 || (*it1)->getVal()==16) && (*this).echecmat((*it1))==1 ){
				if((*this).save2(*it1)==0 && (*this).save(*it1)==0){
					if((*it1)->getVal()==6)
						fichierc= "White win";
					else
						fichierc= "Black win ";

					destText = {120,285,400,100};
					SDL_FreeSurface(text);
					text = TTF_RenderText_Blended(police,fichierc, {0, 0, 0});
					tex = SDL_CreateTextureFromSurface(renderer,text);
					winner=1;
				}
			}
		}
	}
}


/*Ajoute toutes les textures sur le render*/
void Game::render(){
	SDL_RenderClear(renderer);

	if(winner==0){
		carte->Draw();
		draw();
	}
	else{
		carte->Draw();
		draw();
	}
	
	SDL_RenderCopy(renderer, tex,NULL, &destText);
	SDL_RenderPresent(renderer);
}

void Game::draw(){
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(screen[i][j]==1){
				dest.x = j*dest.w;
				dest.y = 50+i*dest.h;
				TextureManager::Draw(pionN,src,dest);
			}
			else if(screen[i][j]==2){
				dest.x = j*dest.w;
				dest.y = 50+i*dest.h;
				TextureManager::Draw(tourN,src,dest);
			}
			else if(screen[i][j]==3){
				dest.x = j*dest.w;
				dest.y = 50+i*dest.h;
				TextureManager::Draw(cavN,src,dest);
			}
			else if(screen[i][j]==4){
				dest.x = j*dest.w;
				dest.y = 50+i*dest.h;
				TextureManager::Draw(fouN,src,dest);
			}
			else if(screen[i][j]==5){
				dest.x = j*dest.w;
				dest.y = 50+i*dest.h;
				TextureManager::Draw(reineN,src,dest);
			}
			else if(screen[i][j]==6){
				dest.x = j*dest.w;
				dest.y = 50+i*dest.h;
				TextureManager::Draw(roiN,src,dest);
			}
			else if(screen[i][j]==11){
				dest.x = j*dest.w;
				dest.y = 50+i*dest.h;
				TextureManager::Draw(pionB,src,dest);
			}
			else if(screen[i][j]==12){
				dest.x = j*dest.w;
				dest.y = 50+i*dest.h;
				TextureManager::Draw(tourB,src,dest);
			}
			else if(screen[i][j]==13){
				dest.x = j*dest.w;
				dest.y = 50+i*dest.h;
				TextureManager::Draw(cavB,src,dest);
			}
			else if(screen[i][j]==14){
				dest.x = j*dest.w;
				dest.y = 50+i*dest.h;
				TextureManager::Draw(fouB,src,dest);
			}
			else if(screen[i][j]==15){
				dest.x = j*dest.w;
				dest.y = 50+i*dest.h;
				TextureManager::Draw(reineB,src,dest);
			}
			else if(screen[i][j]==16){
				dest.x = j*dest.w;
				dest.y = 50+i*dest.h;
				TextureManager::Draw(roiB,src,dest);
			}
				
				
		}
	}
}



