#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include "point.h"

class Figure {
public:
    virtual ~Figure() = default;

    virtual Point center() const = 0;
    virtual operator double() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
    virtual bool equals(const Figure& other) const = 0;
    virtual Figure* clone() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Figure& f) {
        f.print(os);
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Figure& f) {
        f.read(is);
        return is;
    }
};

double polygonArea(const std::vector<Point>& v);
Point polygonCentroid(const std::vector<Point>& v);
bool almostEqual(double a, double b, double eps = 1e-7);
