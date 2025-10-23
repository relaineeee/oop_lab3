#pragma once
#include <vector>
#include <iostream>
#include "figure.h"

class Array {
public:
    Array() = default;

    Array(const Array& other);
    Array& operator=(const Array& other);

    Array(Array&& other);
    Array& operator=(Array&& other);

    ~Array();

    void push(Figure* f);
    void erase(size_t index);
    double totalArea() const;
    void printCentersAndAreas(std::ostream& os) const;
    void printFigures(std::ostream& os) const;

    const Figure* at(size_t index) const;

private:
    std::vector<Figure*> m_data;
    static void deleteAll(std::vector<Figure*>& v);
};
