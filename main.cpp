
   
#include <iostream>
#include <chrono>
#include <thread>
#include "chip8.hpp"

#include "SDL2/SDL.h"






int main()
{
    Chip chip = Chip();
    chip.loadMemory("maze.ch8");
    int width = 1024;
    int height = 512;
    SDL_Window* window = NULL;

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        exit(1);
    }
    window = SDL_CreateWindow("EMULATOR", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_RenderSetLogicalSize(renderer, width, height);

    SDL_Texture* sdlTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888,
    SDL_TEXTUREACCESS_STREAMING, 64, 32);

    uint32_t pixels[2048];
    for(int i = 0; i < 100; i++)
    {
        chip.runEmulator();
        if(chip.drawFlag)
        {
            chip.drawFlag = false;
            for(int j = 0; j < 2048; j++)
            {
                uint8_t pixel = chip.gfx[j];
                pixels[j] = (0x00FFFFFF * pixel) | 0xFF000000;
            }
            SDL_UpdateTexture(sdlTexture, NULL, pixels, 64 * sizeof(Uint32));
            // Clear screen and render
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, sdlTexture, NULL, NULL);
            SDL_RenderPresent(renderer);
        }
        std::this_thread::sleep_for(std::chrono::microseconds(1200));
        
    }
    
    
    return 0;
}

