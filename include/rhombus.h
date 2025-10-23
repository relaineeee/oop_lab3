#pragma once
#include "figure.h"

class Rhombus : public Figure {
public:
    Rhombus();
    Rhombus(const std::vector<Point>& verts);

    Rhombus(const Rhombus& other);
    Rhombus(Rhombus&& other);
    Rhombus& operator=(const Rhombus& other);
    Rhombus& operator=(Rhombus&& other);

    ~Rhombus() = default;

    Point center() const;
    operator double() const;
    void print(std::ostream& os) const;
    void read(std::istream& is);
    bool equals(const Figure& other) const;
    Figure* clone() const;

private:
    std::vector<Point> m_v;
    static bool isRhombus(const std::vector<Point>& v);
};
