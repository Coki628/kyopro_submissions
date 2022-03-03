#pragma once
#include "Point.hpp"

// 内積
template<typename T> T dot(const Point<T> a, const Point<T> b) {
    return a.x*b.x + a.y*b.y;
}
