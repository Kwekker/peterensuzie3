TARGET = main
LIBS = -lmingw32 -lSDL2main -lSDL2
MACLIBS = -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2
CC = g++
CFLAGS = -Wall

.PHONY: default all clean

all: default

OBJECTS = $(patsubst src/%.cpp, %.o, $(wildcard src/*.cpp))
HEADERS = $(wildcard src/*.hpp)

%.o: src/%.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ -Wall

.PRECIOUS: $(TARGET) $(OBJECTS)

mac: $(OBJECTS)
	$(CC) $(OBJECTS) $(MACLIBS) -o $(TARGET)

default: $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $(TARGET) -g

run:
	./main

clean:
	-rm -f *.o
	-rm -f $(TARGET)