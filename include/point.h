#pragma once
#include <iostream>

struct Point {
    double x = 0.0;
    double y = 0.0;
};

bool operator==(const Point& a, const Point& b);
std::ostream& operator<<(std::ostream& os, const Point& p);
std::istream& operator>>(std::istream& is, Point& p);
