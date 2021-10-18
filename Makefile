FLAGS= -g
INCLUDES = -I ./includes
OBJECTS = 

all:
	g++ $(FLAGS) ./src/assemble.cpp -o -L ./lib ./bin/assemble $(INCLUDES) $(OBJECTS)