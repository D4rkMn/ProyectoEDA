#ifndef WINDOWHANDLER_H
#define WINDOWHANDLER_H

#include <SDL2/SDL.h>
#include "Visualization2D/WindowContent/WindowContent.h"

class WindowHandler {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    IWindowContent* content = nullptr;

    int sizeX, sizeY;
    bool running = true;
    bool firstFrame = true;

    void handleStart();
    void handleEvents(SDL_Event* event);
    void handleLoop();
    void renderLoop();
public:
    WindowHandler(const char* windowName, int sizeX, int sizeY);
    virtual ~WindowHandler();

    void processFrame();
    bool isRunning() const { return running; }
};

#endif