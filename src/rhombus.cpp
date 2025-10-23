#include "rhombus.h"
#include <iostream>
#include <stdexcept>
#include <cmath>

Rhombus::Rhombus() {
    m_v.resize(4);
}

Rhombus::Rhombus(const std::vector<Point>& verts) {
    m_v = verts;
    if (m_v.size() != 4 || !isRhombus(m_v)) {
        throw std::invalid_argument("Rhombus: need 4 vertices (convex, equal sides).");
    }
}

Rhombus::Rhombus(const Rhombus& other) {
    m_v = other.m_v;
}

Rhombus::Rhombus(Rhombus&& other) {
    m_v = std::move(other.m_v);
}

Rhombus& Rhombus::operator=(const Rhombus& other) {
    if (this != &other) {
        m_v = other.m_v;
    }
    return *this;
}

Rhombus& Rhombus::operator=(Rhombus&& other) {
    if (this != &other) {
        m_v = std::move(other.m_v);
    }
    return *this;
}

Point Rhombus::center() const {
    return polygonCentroid(m_v);
}

Rhombus::operator double() const {
    return polygonArea(m_v);
}

void Rhombus::print(std::ostream& os) const {
    os << "Rhombus { ";
    for (size_t i = 0; i < m_v.size(); ++i) {
        const Point& p = m_v[i];
        os << p << " ";
    }
    os << "}";
}

void Rhombus::read(std::istream& is) {
    for (size_t i = 0; i < m_v.size(); ++i) {
        if (!(is >> m_v[i])) {
            throw std::runtime_error("Failed to read rhombus vertex");
        }
    }
    if (!isRhombus(m_v)) {
        throw std::invalid_argument("Invalid rhombus geometry");
    }
}

bool Rhombus::equals(const Figure& other) const {
    const Rhombus* o = dynamic_cast<const Rhombus*>(&other);
    if (!o) {
        return false;
    }
    if (o->m_v.size() != m_v.size()) {
        return false;
    }
    for (size_t shift = 0; shift < m_v.size(); ++shift) {
        bool match = true;
        for (size_t i = 0; i < m_v.size(); ++i) {
            if (!(m_v[i] == o->m_v[(i + shift) % m_v.size()])) {
                match = false;
                break;
            }
        }
        if (match) {
            return true;
        }
    }
    return false;
}

Figure* Rhombus::clone() const {
    return new Rhombus(*this);
}

static double dist2(const Point& a, const Point& b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}

static double orientation(const Point& a, const Point& b, const Point& c) {
    double ux = b.x - a.x, uy = b.y - a.y;
    double vx = c.x - b.x, vy = c.y - b.y;
    return ux * vy - uy * vx;
}

bool Rhombus::isRhombus(const std::vector<Point>& v) {
    if (v.size() != 4) {
        return false;
    }

    double d01 = dist2(v[0], v[1]);
    double d12 = dist2(v[1], v[2]);
    double d23 = dist2(v[2], v[3]);
    double d30 = dist2(v[3], v[0]);

    bool eq = almostEqual(d01, d12) && almostEqual(d12, d23) && almostEqual(d23, d30);
    if (!eq) {
        return false;
    }

    double sign = orientation(v[0], v[1], v[2]);
    if (almostEqual(sign, 0.0)) {
        return false;
    }
    for (size_t i = 1; i < 4; ++i) {
        double s = orientation(v[i], v[(i + 1) % 4], v[(i + 2) % 4]);
        if (s * sign <= 0.0) {
            return false;
        }
    }

    return polygonArea(v) > 0.0;
}
