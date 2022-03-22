// On linux compile with:
// g++ -std=c++17 main.cpp glad/src/glad.c -I./glad/include -o prog -lSDL2 -ldl
// On windows compile with (if using mingw)
// g++ main.cpp ./glad/src/glad.c -I./glad/include -o prog.exe -lmingw32 -lSDL2main -lSDL2

// mac
// clang++ main.cpp gameobject.cpp vector.cpp -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2 -o main
#include <iostream>
#include <SDL2/SDL.h>
#include <unistd.h>
#include <ctime>    
#include "gameobject.hpp"
#include "vector.hpp"

#define MS_PER_FRAME 33

int main(int argc, char* argv[]){

    // Create a window data type
    // This pointer will point to the 
    // window that is allocated from SDL_CreateWindow
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

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
            640,
            480,
            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // OpenGL setup the graphics context
    SDL_GLContext context;
    context = SDL_GL_CreateContext(window);

    GameObject obj(window, Vector<>(50, 50), Vector<>(50, 50));

    bool gameIsRunning = true;
    while(gameIsRunning){
        time_t start = time(0);
        SDL_Event event;
        // Start our event loop
        while(SDL_PollEvent(&event)){
            // Handle each specific event

            switch(event.type) {
                case SDL_QUIT: gameIsRunning = false; break;
                case SDL_MOUSEMOTION: 

                    break;
                case SDL_KEYDOWN:
                    obj.setPos(Vector<>(50, 50));
                    obj.setV(Vector<>(0, 0));
                    break;
            }
            
            const Uint8* state = SDL_GetKeyboardState(NULL);
            if(state[SDL_SCANCODE_RIGHT]){
                
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        obj.draw();
        obj.force(Vector<>(0, 1));
        std::cout << obj.getV() << "\n" << std::flush;

        SDL_RenderPresent(renderer);

        time_t now = time(0);
        usleep(1000 * MS_PER_FRAME - (now - start));

        // SDL_GL_SwapWindow(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
