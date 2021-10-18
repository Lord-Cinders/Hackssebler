FLAGS= -g
INCLUDES = -I ./includes
OBJECTS = 

all:
	g++ $(FLAGS) ./src/assemble.cpp -o ./bin/assemble $(INCLUDES) $(OBJECTS)