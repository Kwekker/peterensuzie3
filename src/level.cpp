#include "level.hpp"
#include <cstdio>
#include <cstring>
#include <cstdlib>

Level::Level() {
    
}

Level::Level(const char *file) {
    readFile(file);
}

void Level::readFile(const char *file) {
    FILE* levelFile = std::fopen(file, "r");

    if(levelFile == nullptr) {
        printf("Couldn't open level file %s.", file);
    }

    char s[256];
    std::fgets(s, 256, levelFile);
    size = std::atoi(s);

    std::fgets(s, 256, levelFile);
    width = std::atoi(s);

    std::fgets(s, 256, levelFile);
    height = std::atoi(s);

    data = (uint8_t *) malloc(width * height);
    for(uint8_t j = 0; j < height; j++) {
        std::fgets(s, 256, levelFile);
        memcpy(data + j * width, s, width);
    }

    std::fclose(levelFile);
}

void Level::draw() {
    for(uint8_t j = 0; j < height; j++) {
        for(uint8_t i = 0; i < width; i++) {
            SDL_Rect rect = {i * size, j * size, size, size};
            switch(data[i + j * width]) {
                case '1':
                    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
                    SDL_RenderFillRect(renderer, &rect);
                    break;       
            }
        }
    }
}

uint8_t Level::isPassable(uint16_t i, uint16_t j) {
    return data[i + j * width] == '0';
}

uint8_t Level::getData(uint16_t i, uint16_t j) {
    return data[i + j * width];
}

uint8_t Level::isColliding(uint8_t i, uint8_t j, Duck* duck) {
      
    return 0;
}


/*
.level file:


size of tiles in piiels
width of level in tiles
height of level in tiles
12312121
12211123
...
12312313
entitj things

*/