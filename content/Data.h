#ifndef DATA_H
#define DATA_H

#include "Point.h"

template<typename T>
class Data {
private:
    T content;
    Point embedding;

public:
    Data(const T& content);
    T& getContent();
    const T& getContent() const;
    void setContent(const T& content);
    Point& getEmbedding();
    const Point& getEmbedding() const;
};

#endif