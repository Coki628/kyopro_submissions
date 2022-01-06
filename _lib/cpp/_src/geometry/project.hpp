#pragma once
#include "Point.hpp"
#include "dot.hpp"

// 線分segに対する点pの射影
template<typename T> 
Point<T> project(Segment<T> seg, Point<T> p) {
    auto base = seg.p2 - seg.p1;
    T r = dot(p-seg.p1, base) / base.norm();
    return seg.p1 + base*r;
}
