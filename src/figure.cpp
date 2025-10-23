#include "figure.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

bool almostEqual(double a, double b, double eps) {
    return std::fabs(a - b) <= eps;
}

bool operator==(const Point& a, const Point& b) {
    return almostEqual(a.x, b.x) && almostEqual(a.y, b.y);
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x << " " << p.y << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Point& p) {
    is >> p.x >> p.y;
    return is;
}

double polygonArea(const std::vector<Point>& v) {
    const size_t n = v.size();
    if (n < 3) {
        return 0.0;
    }
    double s = 0.0;
    for (size_t i = 0; i < n; ++i) {
        size_t j = (i + 1) % n;
        s += v[i].x * v[j].y - v[j].x * v[i].y;
    }
    return std::fabs(s) * 0.5;
}

Point polygonCentroid(const std::vector<Point>& v) {
    const size_t n = v.size();
    double A2 = 0.0, cx = 0.0, cy = 0.0;
    for (size_t i = 0; i < n; ++i) {
        size_t j = (i + 1) % n;
        double xi = v[i].x, yi = v[i].y;
        double xj = v[j].x, yj = v[j].y;
        double cross = xi * yj - xj * yi;
        A2 += cross;
        cx += (xi + xj) * cross;
        cy += (yi + yj) * cross;
    }
    cx /= (3.0 * A2);
    cy /= (3.0 * A2);
    return Point{ cx, cy };
}
