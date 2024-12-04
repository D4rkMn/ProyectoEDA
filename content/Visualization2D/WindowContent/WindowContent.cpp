#include "Visualization2D/WindowContent/WindowContent.h"
#include <random>
#include <cmath>

ConcreteContent::ConcreteContent(int sizeX, int sizeY) : sizeX(sizeX), sizeY(sizeY) {
    const size_t numberOfPoints = 500; 
    
    std::random_device rd; // Seed for the random number engine
    std::mt19937 gen(rd()); // Mersenne Twister random number engine
    std::uniform_int_distribution<> distribX(0, sizeX); // Uniform distribution in range [min, max]
    std::uniform_int_distribution<> distribY(0, sizeY); // Uniform distribution in range [min, max]
    
    for (size_t i = 0; i < numberOfPoints; i++) {
        points.emplace_back(distribX(gen), distribY(gen), 10, 30, 33, 110, 255);
    }
}

ConcreteContent::~ConcreteContent() {}

void ConcreteContent::handleEvent(SDL_Window* window, SDL_Event* event) {
    switch (event->type) {
        case SDL_WINDOWEVENT: {
            if (event->window.event == SDL_WINDOWEVENT_RESIZED) {
                SDL_GetWindowSize(window, &sizeX, &sizeY);
            }
            break;
        }
        case SDL_MOUSEMOTION: {
            mouseX = event->motion.x;
            mouseY = event->motion.y;
            break;
        }
        case SDL_MOUSEBUTTONDOWN: {
            if (!mouseDown) {
                if (queryPoint) {
                    resetQuery();
                    delete queryPoint;
                }
                queryPoint = new CanvasPoint(mouseX, mouseY, 10, 9, 66, 229);
                mouseDown = true;
            }
            break;
        }
        case SDL_MOUSEBUTTONUP: {
            mouseDown = false;
            break;
        }
        case SDL_KEYDOWN: {
            if (queryStart) break;
            switch (event->key.keysym.sym) {
                case SDLK_1: currentQuery = QueryType::MMR; break;
                case SDLK_2: currentQuery = QueryType::SWAP; break;
                case SDLK_3: currentQuery = QueryType::MOTLEY; break;
                case SDLK_4: currentQuery = QueryType::BRID; break;
                case SDLK_RETURN: {
                    if (queryPoint) {
                        runningQuery = queryStart = true;
                    }
                    break;
                }
            }
            break;
        }
    }
}

static void drawThickLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int thickness) {
    int dx = x2 - x1;
    int dy = y2 - y1;

    // Calculate the angle of the line
    float angle = atan2(dy, dx);
    
    // Loop to draw multiple lines with thickness
    for (int i = -thickness / 2; i <= thickness / 2; ++i) {
        int offsetX = (int)(i * cos(angle + M_PI / 2)); // Perpendicular to the line
        int offsetY = (int)(i * sin(angle + M_PI / 2)); // Perpendicular to the line
        
        // Draw the line with offset to simulate thickness
        SDL_RenderDrawLine(renderer, x1 + offsetX, y1 + offsetY, x2 + offsetX, y2 + offsetY);
    }
}

void ConcreteContent::render(SDL_Renderer* renderer) {
    for (size_t i = 0; i < points.size(); i++) {
        points[i].render(renderer);
    }
    for (size_t i = 0; i < lines.size(); i++) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        drawThickLine(renderer,
            lines[i].first.coordinates[0], lines[i].first.coordinates[1],
            lines[i].second.coordinates[0], lines[i].second.coordinates[1],
            5
        );
        drawThickLine(renderer,
            lines[i].second.coordinates[0], lines[i].second.coordinates[1],
            lines[i].first.coordinates[0], lines[i].first.coordinates[1],
            5
        );
    }
    for (size_t i = 0; i < circles.size(); i++) {
        CanvasPoint::drawCircumference(renderer, circles[i].first.coordinates[0], circles[i].first.coordinates[1], circles[i].second);
    }
    if (queryPoint) queryPoint->render(renderer);
    if (runningQuery) renderQuery(renderer);
}

void ConcreteContent::renderQuery(SDL_Renderer* renderer) {
    if (queryStart) {
        processQuery(renderer);
    }
    queryStart = false;
}