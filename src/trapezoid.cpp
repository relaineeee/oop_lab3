#include "trapezoid.h"
#include <iostream>
#include <stdexcept>

Trapezoid::Trapezoid() {
    m_v.resize(4);
}

Trapezoid::Trapezoid(const std::vector<Point>& verts) {
    m_v = verts;
    if (m_v.size() != 4 || !isTrapezoid(m_v)) {
        throw std::invalid_argument("Trapezoid: need 4 vertices (convex, at least one pair of parallel sides).");
    }
}

Trapezoid::Trapezoid(const Trapezoid& other) {
    m_v = other.m_v;
}

Trapezoid::Trapezoid(Trapezoid&& other) {
    m_v = std::move(other.m_v);
}

Trapezoid& Trapezoid::operator=(const Trapezoid& other) {
    if (this != &other) {
        m_v = other.m_v;
    }
    return *this;
}

Trapezoid& Trapezoid::operator=(Trapezoid&& other) {
    if (this != &other) {
        m_v = std::move(other.m_v);
    }
    return *this;
}

Point Trapezoid::center() const {
    return polygonCentroid(m_v);
}

Trapezoid::operator double() const {
    return polygonArea(m_v);
}

void Trapezoid::print(std::ostream& os) const {
    os << "Trapezoid { ";
    for (size_t i = 0; i < m_v.size(); ++i) {
        const Point& p = m_v[i];
        os << p << " ";
    }
    os << "}";
}

void Trapezoid::read(std::istream& is) {
    for (size_t i = 0; i < m_v.size(); ++i) {
        if (!(is >> m_v[i])) {
            throw std::runtime_error("Failed to read trapezoid vertex");
        }
    }
    if (!isTrapezoid(m_v)) {
        throw std::invalid_argument("Invalid trapezoid geometry");
    }
}

bool Trapezoid::equals(const Figure& other) const {
    const Trapezoid* o = dynamic_cast<const Trapezoid*>(&other);
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

Figure* Trapezoid::clone() const {
    return new Trapezoid(*this);
}

static inline Point diff(const Point& a, const Point& b) {
    return Point{ a.x - b.x, a.y - b.y };
}

static inline double cross(const Point& u, const Point& w) {
    return u.x * w.y - u.y * w.x;
}

static double orientation(const Point& a, const Point& b, const Point& c) {
    double ux = b.x - a.x, uy = b.y - a.y;
    double vx = c.x - b.x, vy = c.y - b.y;
    return ux * vy - uy * vx;
}

bool Trapezoid::isTrapezoid(const std::vector<Point>& v) {
    if (v.size() != 4) {
        return false;
    }

    Point AB = diff(v[1], v[0]);
    Point BC = diff(v[2], v[1]);
    Point CD = diff(v[3], v[2]);
    Point DA = diff(v[0], v[3]);

    bool pair1 = almostEqual(cross(AB, CD), 0.0);
    bool pair2 = almostEqual(cross(BC, DA), 0.0);
    if (!(pair1 || pair2)) {
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
