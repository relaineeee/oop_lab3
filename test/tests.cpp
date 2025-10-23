#include <gtest/gtest.h>
#include <stdexcept>
#include <cmath>

#include "figure.h"
#include "trapezoid.h"
#include "rhombus.h"
#include "pentagon.h"
#include "array.h"

static double eps() { return 1e-6; }

TEST(UtilsTest, PolygonAreaTriangle) {
    std::vector<Point> v;
    v.push_back(Point{0.0, 0.0});
    v.push_back(Point{4.0, 0.0});
    v.push_back(Point{0.0, 3.0});
    double a = polygonArea(v);
    EXPECT_NEAR(a, 6.0, eps());
}

TEST(TrapezoidTest, ValidConstructionAreaAndCenter) {
    std::vector<Point> v;
    v.push_back(Point{-2.0, 0.0});
    v.push_back(Point{ 2.0, 0.0});
    v.push_back(Point{ 1.0, 2.0});
    v.push_back(Point{-1.0, 2.0});

    Trapezoid t(v);
    double area = static_cast<double>(t);
    EXPECT_NEAR(area, 6.0, eps());

    Point c = t.center();
    EXPECT_NEAR(c.x, 0.0, eps());
    EXPECT_NEAR(c.y, 8.0 / 9.0, 1e-6);
}

TEST(TrapezoidTest, InvalidNoParallelSides) {
    std::vector<Point> v;
    v.push_back(Point{0.0, 0.0});
    v.push_back(Point{3.0, 0.5});
    v.push_back(Point{2.0, 2.0});
    v.push_back(Point{-0.5, 1.5});
    EXPECT_THROW(Trapezoid t(v), std::invalid_argument);
}

TEST(TrapezoidTest, EqualsWithCyclicShift) {
    std::vector<Point> a;
    a.push_back(Point{0.0, 0.0});
    a.push_back(Point{4.0, 0.0});
    a.push_back(Point{3.0, 2.0});
    a.push_back(Point{1.0, 2.0});
    std::vector<Point> b;
    b.push_back(Point{4.0, 0.0});
    b.push_back(Point{3.0, 2.0});
    b.push_back(Point{1.0, 2.0});
    b.push_back(Point{0.0, 0.0});

    Trapezoid t1(a);
    Trapezoid t2(b);
    EXPECT_TRUE(t1.equals(t2));
}

TEST(RhombusTest, ValidSquareAsRhombus) {
    std::vector<Point> v;
    v.push_back(Point{0.0, 0.0});
    v.push_back(Point{1.0, 0.0});
    v.push_back(Point{1.0, 1.0});
    v.push_back(Point{0.0, 1.0});

    Rhombus r(v);
    EXPECT_NEAR(static_cast<double>(r), 1.0, eps());
    Point c = r.center();
    EXPECT_NEAR(c.x, 0.5, eps());
    EXPECT_NEAR(c.y, 0.5, eps());
}

TEST(RhombusTest, InvalidNotAllSidesEqual) {
    std::vector<Point> v;
    v.push_back(Point{0.0, 0.0});
    v.push_back(Point{2.0, 0.0});
    v.push_back(Point{2.0, 1.0});
    v.push_back(Point{0.0, 1.0});
    EXPECT_THROW(Rhombus r(v), std::invalid_argument);
}

TEST(RhombusTest, EqualsWithCyclicShift) {
    std::vector<Point> a;
    a.push_back(Point{0.0, 0.0});
    a.push_back(Point{1.0, 0.0});
    a.push_back(Point{1.0, 1.0});
    a.push_back(Point{0.0, 1.0});
    std::vector<Point> b;
    b.push_back(Point{1.0, 0.0});
    b.push_back(Point{1.0, 1.0});
    b.push_back(Point{0.0, 1.0});
    b.push_back(Point{0.0, 0.0});

    Rhombus r1(a);
    Rhombus r2(b);
    EXPECT_TRUE(r1.equals(r2));
}

TEST(PentagonTest, ValidRegularPentagonOnUnitCircle) {
    std::vector<Point> v;
    const double pi = 3.14159265358979323846;
    const double step = 2.0 * pi / 5.0;
    size_t i = 0;
    for (i = 0; i < 5; ++i) {
        double ang = i * step;
        v.push_back(Point{ std::cos(ang), std::sin(ang) });
    }

    Pentagon p(v);
    double area = static_cast<double>(p);
    double expected = 2.5 * std::sin(72.0 * pi / 180.0);
    EXPECT_NEAR(area, expected, 1e-6);

    Point c = p.center();
    EXPECT_NEAR(c.x, 0.0, 1e-15);
    EXPECT_NEAR(c.y, 0.0, 1e-15);
}

TEST(PentagonTest, InvalidIfAnglesNotEqual) {
    std::vector<Point> v;
    const double pi = 3.14159265358979323846;
    const double step = 2.0 * pi / 5.0;
    size_t i = 0;
    for (i = 0; i < 5; ++i) {
        double ang = i * step;
        v.push_back(Point{ std::cos(ang), std::sin(ang) });
    }
    v[2].x += 0.05;
    EXPECT_THROW(Pentagon p(v), std::invalid_argument);
}

TEST(PentagonTest, EqualsWithCyclicShift) {
    std::vector<Point> a;
    std::vector<Point> b;
    const double pi = 3.14159265358979323846;
    const double step = 2.0 * pi / 5.0;
    size_t i = 0;
    for (i = 0; i < 5; ++i) {
        double ang = i * step;
        a.push_back(Point{ std::cos(ang), std::sin(ang) });
    }
    for (i = 0; i < 5; ++i) {
        b.push_back(a[(i + 2) % 5]);
    }

    Pentagon p1(a);
    Pentagon p2(b);
    EXPECT_TRUE(p1.equals(p2));
}

TEST(ArrayTest, PushTotalAreaAndErase) {
    Array arr;

    std::vector<Point> tv;
    tv.push_back(Point{-2.0, 0.0});
    tv.push_back(Point{ 2.0, 0.0});
    tv.push_back(Point{ 1.0, 2.0});
    tv.push_back(Point{-1.0, 2.0});
    Trapezoid* t = new Trapezoid(tv);
    arr.push(t);

    std::vector<Point> rv;
    rv.push_back(Point{0.0, 0.0});
    rv.push_back(Point{1.0, 0.0});
    rv.push_back(Point{1.0, 1.0});
    rv.push_back(Point{0.0, 1.0});
    Rhombus* r = new Rhombus(rv);
    arr.push(r);

    double expectedSum = static_cast<double>(*t) + static_cast<double>(*r);
    EXPECT_NEAR(arr.totalArea(), expectedSum, eps());

    arr.erase(0);
    EXPECT_NEAR(arr.totalArea(), static_cast<double>(*r), eps());

    EXPECT_NO_THROW(arr.at(0));
    EXPECT_THROW(arr.at(1), std::out_of_range);
}

TEST(ArrayTest, CopyClonesFigures) {
    Array arr;

    std::vector<Point> rv;
    rv.push_back(Point{0.0, 0.0});
    rv.push_back(Point{1.0, 0.0});
    rv.push_back(Point{1.0, 1.0});
    rv.push_back(Point{0.0, 1.0});
    arr.push(new Rhombus(rv));

    Array copy(arr);
    const Figure* a = arr.at(0);
    const Figure* b = copy.at(0);
    EXPECT_TRUE(a->equals(*b));
    EXPECT_THROW(copy.at(1), std::out_of_range);
}

TEST(ArrayTest, MoveAssignWorks) {
    Array arr;

    std::vector<Point> tv;
    tv.push_back(Point{-2.0, 0.0});
    tv.push_back(Point{ 2.0, 0.0});
    tv.push_back(Point{ 1.0, 2.0});
    tv.push_back(Point{-1.0, 2.0});
    Trapezoid* t = new Trapezoid(tv);
    double ta = static_cast<double>(*t);
    arr.push(t);

    Array other;
    other = std::move(arr);

    EXPECT_NEAR(other.totalArea(), ta, eps());
    EXPECT_THROW(arr.at(0), std::out_of_range);
}
