CC = g++ -g -std=c++11
CFLAGS = -Wall
LDFLAGS = `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -lSDL_Mixer

SRC = Cavalier.cc Roi.cc Reine.cc Fou.cc Tour.cc Piece.cc Pion.cc Game.cc Map.cc TextureManager.cc main.cc
OBJ = $(SRC:.cc=.o)
EXEC = main


all: $(EXEC)

%.o: %.cc
	$(CC) $(CFLAGS) -o $@ -c $< 

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	
clean:
	rm -f *.o $(EXEC)  
