#include "array.h"
#include <iostream>
#include <stdexcept>
#include <utility>

void Array::deleteAll(std::vector<Figure*>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        delete v[i];
    }
    v.clear();
}

Array::Array(const Array& other) {
    m_data.reserve(other.m_data.size());
    try {
        for (size_t i = 0; i < other.m_data.size(); ++i) {
            Figure* orignal = other.m_data[i];
            m_data.push_back(orignal ? orignal->clone() : nullptr);
        }
    } catch (...) {
        deleteAll(m_data);
        throw;
    }
}

Array& Array::operator=(const Array& other) {
    if (this == &other) {
        return *this;
    }

    std::vector<Figure*> tmp;
    tmp.reserve(other.m_data.size());
    try {
        for (size_t i = 0; i < other.m_data.size(); ++i) {
            Figure* orignal = other.m_data[i];
            tmp.push_back(orignal ? orignal->clone() : nullptr);
        }
    } catch (...) {
        for (size_t j = 0; j < tmp.size(); ++j) {
            delete tmp[j];
        }
        throw;
    }

    deleteAll(m_data);
    m_data = std::move(tmp);
    return *this;
}

Array::Array(Array&& other) {
    m_data = std::move(other.m_data);
    other.m_data.clear();
}

Array& Array::operator=(Array&& other) {
    if (this != &other) {
        deleteAll(m_data);
        m_data = std::move(other.m_data);
        other.m_data.clear();
    }
    return *this;
}

Array::~Array() {
    deleteAll(m_data);
}

void Array::push(Figure* f) {
    if (!f) {
        throw std::invalid_argument("push: null pointer");
    }
    m_data.push_back(f);
}

void Array::erase(size_t index) {
    if (index >= m_data.size()) {
        throw std::out_of_range("Index out of range");
    }
    delete m_data[index];
    m_data.erase(m_data.begin() + index);
}

double Array::totalArea() const {
    double sum = 0.0;
    for (size_t i = 0; i < m_data.size(); ++i) {
        sum += *(m_data[i]);
    }
    return sum;
}

void Array::printCentersAndAreas(std::ostream& os) const {
    for (size_t i = 0; i < m_data.size(); ++i) {
        const Figure* f = m_data[i];
        Point c = f->center();
        double A = *f;
        os << i+1 << ")" << " center=(" << c.x << " " << c.y << ") area=" << A << "\n";
    }
}

void Array::printFigures(std::ostream& os) const {
    for (size_t i = 0; i < m_data.size(); ++i) {
        os << "#" << i << " " << *m_data[i] << "\n";
    }
}

const Figure* Array::at(size_t index) const {
    if (index >= m_data.size()) {
        throw std::out_of_range("Index out of range");
    }
    return m_data[index];
}
