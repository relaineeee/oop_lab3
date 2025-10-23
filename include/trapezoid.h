#pragma once
#include "figure.h"

class Trapezoid : public Figure {
public:
    Trapezoid();
    Trapezoid(const std::vector<Point>& verts);

    Trapezoid(const Trapezoid& other);
    Trapezoid(Trapezoid&& other);
    Trapezoid& operator=(const Trapezoid& other);
    Trapezoid& operator=(Trapezoid&& other);

    ~Trapezoid() = default;

    Point center() const;
    operator double() const;
    void print(std::ostream& os) const;
    void read(std::istream& is);
    bool equals(const Figure& other) const;
    Figure* clone() const;

private:
    std::vector<Point> m_v;
    static bool isTrapezoid(const std::vector<Point>& v);
};
