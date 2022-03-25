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

    char s[256];
    std::fgets(s, 256, levelFile);
    tileWidth = std::atoi(s);

    std::fgets(s, 256, levelFile);
    width = std::atoi(s);

    std::fgets(s, 256, levelFile);
    height = std::atoi(s);

    data = (uint8_t *) malloc(width * height);
    for(uint8_t y = 0; y < height; y++) {
        std::fgets(s, 256, levelFile);
        memcpy(data + y * width, s, width);
    }

    std::fclose(levelFile);
}

void Level::draw() {
    for(uint8_t y = 0; y < height; y++) {
        for(uint8_t x = 0; x < width; x++) {
            std::cout << data[x + y * width];
        }
        std::cout << '\n';
    }
}

/*
size of tiles in pixels
12312121
12211123
...
12312313
end <- literally the word end
entity things
 */