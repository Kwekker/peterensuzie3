#include "level.hpp"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "box.hpp"
#include "duck.hpp"

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
    width = std::strchr(s, '\n') - s + 1;

    while(s[0] != '\n') {
        std::fgets(s, 256, levelFile);
        height++;
    }

    std::rewind(levelFile);

    data = (uint8_t *) malloc(width * height) + 1;
    for(uint16_t i = 0; i < height; i++) {
        std::fgets(s, 256, levelFile);
        memcpy(data + i * width, s, width);
    }
    data [width * height] = 0;

    std::fgets(s, 50, levelFile);   //Empty line
    std::fgets(s, 50, levelFile);   //Size of each tile
    size = std::atoi(s);

    std::fgets(s, 50, levelFile);
    elementsAmount = std::atoi(s);
    elements = (GameObject **) malloc(elementsAmount * sizeof(GameObject *));

    for(uint8_t i = 0; i < elementsAmount; i++) {
        std::fgets(s, 256, levelFile);
        if(s[0] == 'b') {
            Vector pos = Vector(std::atoi(s + 4), std::atoi(s + 8)) * size * 16;
            Vector size(std::atoi(s + 12), std::atoi(s + 16));
            elements[i] = new Box(pos, size, this);
        }
        else if(s[0] == 'd') {
            Vector pos = Vector(std::atoi(s + 4), std::atoi(s + 8)) * size * 16;
            Vector size(std::atoi(s + 12), std::atoi(s + 16));
            player = new Duck(pos, size, this);
            elements[i] = player;
        }
    }

    std::cout << "Level size: " << (int)size << "  x: " << width << "  y: " << height << std::endl;
    std::cout << "Found " << (int)elementsAmount << " elements of size " << sizeof(GameObject) << "." << std::endl;

    std::fclose(levelFile);
    std::cout << "file closed" << std::endl;

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

void Level::run(uint8_t frame, const uint8_t* state) {
    player->handleKey(state, frame);
    for(uint8_t i = 0; i < elementsAmount; i++) {
        elements[i]->draw(frame);
    }
}

void Level::mouse(uint8_t button, int16_t x, int16_t y) {
    for(uint8_t i = 0; i < elementsAmount; i++) {
        elements[i]->mouse(button, x, y);
    }
}

uint8_t Level::isPassable(uint16_t i, uint16_t j) {
    return data[i + j * width] == '0';
}

uint8_t Level::getData(uint16_t i, uint16_t j) {
    return data[i + j * width];
}

Duck* Level::getPlayer() {
    return player;
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