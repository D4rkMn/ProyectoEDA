#include <iostream>
#include "Visualization2D/WindowHandler/WindowHandler.h"

int main() {
    WindowHandler window("name", 1600, 900);
    while (window.isRunning()) {
        window.processFrame();
    }
    return 0;
}