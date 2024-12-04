#ifndef CANVASPOINT_H
#define CANVASPOINT_H

#include <SDL2/SDL.h>
#include "DataStructures/Point/Point.h"

class CanvasPoint {
private:
    SDL_Point point;
    SDL_Color color;
    int size;
    bool isCircle = true;
public:
    CanvasPoint(int x, int y, int size, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) : size(size) {
        point = SDL_Point{x, y};
        color = SDL_Color{r, g, b, a};
        isCircle = true;
    }

    static void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
        // Loop through the radius in vertical steps
        for (int y = -radius; y <= radius; ++y) {
            for (int x = -radius; x <= radius; ++x) {
                // Check if the point (x, y) lies inside the circle
                if (x * x + y * y <= radius * radius) {
                    SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
                }
            }
        }
    }

    static void drawCircumference(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
        const int32_t diameter = (radius * 2);

        int32_t x = (radius - 1);
        int32_t y = 0;
        int32_t tx = 1;
        int32_t ty = 1;
        int32_t error = (tx - diameter);

        while (x >= y)
        {
            //  Each of the following renders an octant of the circle
            SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);
            SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
            SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
            SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
            SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
            SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
            SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);
            SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);

            if (error <= 0)
            {
                ++y;
                error += ty;
                ty += 2;
            }

            if (error > 0)
            {
                --x;
                tx += 2;
                error += (tx - diameter);
            }
        }
    }

    Point toPoint() const {
        Point result(2);
        result.coordinates[0] = point.x;
        result.coordinates[1] = point.y;
        return result;
    }

    void render(SDL_Renderer* renderer) {
        if (isCircle) {
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            CanvasPoint::drawCircle(renderer, point.x, point.y, size);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            CanvasPoint::drawCircumference(renderer, point.x, point.y, size);
        }
        else {
            SDL_Rect rect{point.x-size, point.y-size, 2*size, 2*size};
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);   
            SDL_RenderFillRect(renderer, &rect);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &rect);
        }
    } 

    friend class ConcreteContent;
};

#endif