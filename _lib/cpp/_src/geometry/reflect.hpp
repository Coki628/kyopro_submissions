#include "Segment.hpp"
#include "Point.hpp"
#include "project.hpp"

// 線分segを対称軸とした点pの線対称の点
template<typename T>
Point<T> reflect(Segment<T> seg, Point<T> p) {
    return p + (project(seg, p) - p) * (T)2;
}
