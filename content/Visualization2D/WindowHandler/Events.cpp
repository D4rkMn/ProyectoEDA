#include "Visualization2D/WindowHandler/WindowHandler.h"

void WindowHandler::handleEvents(SDL_Event* event) {
    if (content) content->handleEvent(window, event);
}

void WindowHandler::handleStart() {
    content = new ConcreteContent(sizeX, sizeY);
}

void WindowHandler::renderLoop() {
    if (content) {
        content->render(renderer);
    }
}