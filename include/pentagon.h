#pragma once
#include "figure.h"

class Pentagon : public Figure {
public:
    Pentagon();
    Pentagon(const std::vector<Point>& verts);

    Pentagon(const Pentagon& other);
    Pentagon(Pentagon&& other);
    Pentagon& operator=(const Pentagon& other);
    Pentagon& operator=(Pentagon&& other);

    ~Pentagon() = default;

    Point center() const;
    operator double() const;
    void print(std::ostream& os) const;
    void read(std::istream& is);
    bool equals(const Figure& other) const;
    Figure* clone() const;

private:
    std::vector<Point> m_v;
    static bool isPentagon(const std::vector<Point>& v);
};
