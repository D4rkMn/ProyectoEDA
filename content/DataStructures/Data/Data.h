#ifndef DATA_H
#define DATA_H

#include "DataStructures/Point/Point.h"

template<typename T>
class Data {
private:
    T content;
    Point embedding;

public:
    // Constructor
    Data() = default;
    Data(const T& content) : content(content) {}

    // Métodos para obtener y modificar el contenido
    T& getContent() { 
        return content; 
    }
    
    const T& getContent() const { 
        return content; 
    }
    
    void setContent(const T& newContent) { 
        content = newContent; 
    }

    // Métodos para el embedding
    Point& getEmbedding() { 
        return embedding; 
    }
    
    const Point& getEmbedding() const { 
        return embedding; 
    }

    // Operadores
    bool operator==(const Data<T>& other) const {
        return this->content == other.content;
    }

    bool operator<(const Data<T>& other) const {
        return this->content < other.content;
    }

    // Método getJA - versiones const y no-const
    T getJA() { 
        return 2; 
    }
    
    T getJA() const { 
        return 2; 
    }
};

#endif // DATA_H