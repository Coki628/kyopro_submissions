#include "../macros.hpp"
#include "Point.hpp"

template<typename T>
struct Circle {
    Point<T> c;
    ld r;
    Circle(Point<T> c={0, 0}, ld r=0.0) : c(c), r(r) {}
};
