#include "Data.h"

template<typename T>
Data<T>::Data(const T& content) : content(content) {}

template<typename T>
T& Data<T>::getContent() {
    return content;
}

template<typename T>
const T& Data<T>::getContent() const {
    return content;
}

template<typename T>
void Data<T>::setContent(const T& newContent) {
    content = newContent;
}

template<typename T>
Point& Data<T>::getEmbedding() {
    return embedding;
}

template<typename T>
const Point& Data<T>::getEmbedding() const {
    return embedding;
}