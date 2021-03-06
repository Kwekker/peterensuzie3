// On linux compile with:
// g++ -std=c++17 main.cpp glad/src/glad.c -I./glad/include -o prog -lSDL2 -ldl
// On windows compile with (if using mingw)
// g++ main.cpp ./glad/src/glad.c -I./glad/include -o prog.exe -lmingw32 -lSDL2main -lSDL2

// mac
// bash compile.sh

#include <iostream>
#include <SDL2/SDL.h>
#include <unistd.h>
#include <ctime>    
#include "globals.hpp"
#include "level.hpp"
#include "duck.hpp"
#include "vector.hpp"

uint8_t FPS = 40;
#define MS_PER_FRAME 1000 / FPS

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
int16_t width, height;

int main(int argc, char* argv[]){

    // Initialize the video subsystem.
    // If it returns less than 1, then an
    // error code will be received.
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not be initialized: " <<
                  SDL_GetError();
    }else{
        std::cout << "SDL video system is ready to go\n";
    }
    // Before we create our window, specify OpenGL version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);


    window = SDL_CreateWindow("Kleine poezen window :)",
            20,
            20,
            1020,
            720,
            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //Start of game variables
    Level level("./lvl/1.level");
    uint8_t frame = 0xff;

    bool gameIsRunning = true;
    while(gameIsRunning) {
        time_t start = time(0);
        const uint8_t *keyBoardState = SDL_GetKeyboardState(NULL);

        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type) {
                case SDL_QUIT: gameIsRunning = false; break;
                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.button == 1 || event.button.button == 3) level.mouse(event.button.button, event.button.x, event.button.y);
                    break;
                case SDL_MOUSEBUTTONUP:
                    if(event.button.button == 1 || event.button.button == 3) level.mouse(0, event.button.x, event.button.y);
                    break;

                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_f && event.key.repeat == 0) {
                        frame = 0;
                    }
                    break;
                case SDL_KEYUP:
                    if(!keyBoardState[SDL_SCANCODE_F]) frame = 0xff;
                    break;
            }
        }
        if(keyBoardState[SDL_SCANCODE_H])FPS = 1;
        else FPS = 40;
        
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        level.draw();
        if(frame < 0xff) frame = (frame + 1) & 0xf;
        
        level.run(frame, keyBoardState);

        SDL_RenderPresent(renderer);

        //Gameloop shenanigans
        time_t now = time(0);
        usleep(1000 * MS_PER_FRAME - (now - start));
    }
    std::cout << "Goodbye!\n" << std::flush;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
