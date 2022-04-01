#OBJS specifies which files to compile as part of the project
OBJS := $(shell find $(SOURCEDIR) -name '*.cpp')

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = winmain

#This is the target that compiles our executable
all : $(OBJS)
	g++ $(OBJS) -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -o $(OBJ_NAME)

fast : $(OBJS)
	g++ $(OBJS) -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -O0 -o $(OBJ_NAME)

run : $(OBJ_NAME)
	./$(OBJ_NAME)