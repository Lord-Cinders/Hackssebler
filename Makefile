FLAGS= -g
INCLUDES = -I ./includes
OBJECTS = 

all:
	g++ $(FLAGS)  ./src/main.cpp $(INCLUDES) -o ./bin/main