#include "Visualization2D/WindowHandler/WindowHandler.h"

WindowHandler::WindowHandler(const char* windowName, int sizeX, int sizeY) : sizeX(sizeX), sizeY(sizeY) {
    window = SDL_CreateWindow (
        windowName,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        sizeX, sizeY,
        SDL_WINDOW_SHOWN
    );
    
    if (!window) {
        fprintf(stderr, "Error creating window.\n");
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        fprintf(stderr, "Error creating renderer.\n");
        return;
    }
}

WindowHandler::~WindowHandler() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    if (content) delete content;
    SDL_Quit();
}

void WindowHandler::handleLoop() {
    SDL_SetRenderDrawColor(renderer, 199, 229, 255, 255);
    SDL_RenderClear(renderer);
    renderLoop();
    SDL_RenderPresent(renderer);
}

void WindowHandler::processFrame() {
    if (firstFrame) {
        firstFrame = false;
        handleStart();
    }
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: {
                running = false;
                return;
                break;
            }
            case SDL_WINDOWEVENT: {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    SDL_GetWindowSize(window, &sizeX, &sizeY);
                }
                break;
            }
        }
        handleEvents(&event);
    }
    handleLoop();
}