#include "pentagon.h"
#include <iostream>
#include <stdexcept>
#include <cmath>

Pentagon::Pentagon() {
    m_v.resize(5);
}

Pentagon::Pentagon(const std::vector<Point>& verts) {
    m_v = verts;
    if (m_v.size() != 5 || !isPentagon(m_v)) {
        throw std::invalid_argument("Pentagon: need 5 vertices (convex, equal sides, equal angles).");
    }
}

Pentagon::Pentagon(const Pentagon& other) {
    m_v = other.m_v;
}

Pentagon::Pentagon(Pentagon&& other) {
    m_v = std::move(other.m_v);
}

Pentagon& Pentagon::operator=(const Pentagon& other) {
    if (this != &other) {
        m_v = other.m_v;
    }
    return *this;
}

Pentagon& Pentagon::operator=(Pentagon&& other) {
    if (this != &other) {
        m_v = std::move(other.m_v);
    }
    return *this;
}

Point Pentagon::center() const {
    return polygonCentroid(m_v);
}

Pentagon::operator double() const {
    return polygonArea(m_v);
}

void Pentagon::print(std::ostream& os) const {
    os << "Pentagon { ";
    for (size_t i = 0; i < m_v.size(); ++i) {
        const Point& p = m_v[i];
        os << p << " ";
    }
    os << "}";
}

void Pentagon::read(std::istream& is) {
    for (size_t i = 0; i < m_v.size(); ++i) {
        if (!(is >> m_v[i])) {
            throw std::runtime_error("Failed to read pentagon vertex");
        }
    }
    if (!isPentagon(m_v)) {
        throw std::invalid_argument("Invalid regular pentagon geometry");
    }
}

bool Pentagon::equals(const Figure& other) const {
    const Pentagon* o = dynamic_cast<const Pentagon*>(&other);
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

Figure* Pentagon::clone() const {
    return new Pentagon(*this);
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

static double angleCos(const Point& a, const Point& b, const Point& c) {
    double ux = a.x - b.x, uy = a.y - b.y;
    double vx = c.x - b.x, vy = c.y - b.y;
    double du = std::sqrt(ux * ux + uy * uy);
    double dv = std::sqrt(vx * vx + vy * vy);
    if (du == 0.0 || dv == 0.0) {
        return 1.0;
    }
    return (ux * vx + uy * vy) / (du * dv);
}

bool Pentagon::isPentagon(const std::vector<Point>& v) {
    if (v.size() != 5) {
        return false;
    }

    double d0 = dist2(v[0], v[1]);
    for (size_t i = 1; i < 5; ++i) {
        if (!almostEqual(d0, dist2(v[i], v[(i + 1) % 5]))) {
            return false;
        }
    }

    double sign = orientation(v[0], v[1], v[2]);
    if (almostEqual(sign, 0.0)) {
        return false;
    }
    for (size_t i = 1; i < 5; ++i) {
        double s = orientation(v[i], v[(i + 1) % 5], v[(i + 2) % 5]);
        if (s * sign <= 0.0) {
            return false;
        }
    }

    double c0 = angleCos(v[4], v[0], v[1]);
    for (size_t i = 1; i < 5; ++i) {
        double ci = angleCos(v[i - 1], v[i], v[(i + 1) % 5]);
        if (!almostEqual(c0, ci, 1e-6)) {
            return false;
        }
    }

    return polygonArea(v) > 0.0;
}
