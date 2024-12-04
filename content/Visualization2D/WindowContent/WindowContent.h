#ifndef WINDOWCONTENT_H
#define WINDOWCONTENT_H

#include <SDL2/SDL.h>
#include <vector>
#include "Visualization2D/CanvasPoint/CanvasPoint.h"

class IWindowContent {
public:
    IWindowContent() {};
    virtual ~IWindowContent() {}
    virtual void handleEvent(SDL_Window*, SDL_Event*) = 0;
    virtual void render(SDL_Renderer*) = 0;
};

class ConcreteContent : public IWindowContent {
private:
    std::vector<CanvasPoint> points;
    std::vector<std::pair<Point, Point>> lines;
    std::vector<std::pair<Point, int>> circles;
    CanvasPoint* queryPoint = nullptr;
    int sizeX, sizeY;
    int mouseX, mouseY;
    bool mouseDown = false;

    enum class QueryType {
        MMR = 1,
        SWAP = 2,
        MOTLEY = 3,
        BRID = 4
    };
    QueryType currentQuery = QueryType::MMR;
    bool queryStart = false;
    bool runningQuery = false;

public:
    ConcreteContent(int, int);
    ~ConcreteContent();
    void handleEvent(SDL_Window*, SDL_Event*) override;
    void render(SDL_Renderer*) override;
    void renderQuery(SDL_Renderer*);
    void resetQuery();
    void processQuery(SDL_Renderer*);
};

#endif