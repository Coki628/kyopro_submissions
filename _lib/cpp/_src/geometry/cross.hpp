#pragma once
#include "Point.hpp"

// 外積
template<typename T> T cross(const Point<T> a, const Point<T> b) { return a.x*b.y - a.y*b.x; }
