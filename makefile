TARGET = main
LIBS = -lmingw32 -lSDL2main -lSDL2
MACLIBS = -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2
CC = g++
CFLAGS = -Wall

.PHONY: default all clean

all: default

OBJECTS = $(patsubst src/%.cpp, obj/%.o, $(wildcard src/*.cpp))
HEADERS = $(wildcard src/*.hpp)

obj/%.o: src/%.cpp $(HEADERS)

	$(CC) $(CFLAGS) -c $< -o $@ -Wall -std=c++11

.PRECIOUS: $(TARGET) $(OBJECTS)

mac: $(OBJECTS)
	clang++ $(OBJECTS) $(MACLIBS) -o $(TARGET)

default: $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $(TARGET) -g

run:
	./main

clean:
	-rm -f obj/*.o
	-rm -f $(TARGET)