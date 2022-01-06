#include "Point.hpp"

// 線分p0,p1から線分p0,p2への回転方向
template<typename T>
ll ccw(Point<T> p0, Point<T> p1, Point<T> p2) {
    Point<T> a = p1-p0;
    Point<T> b = p2-p0;
    // 反時計回り
    if (cross(a, b) > EPS) return 1;
    // 時計回り
    if (cross(a, b) < -EPS) return -1;
    // 直線上(p2 => p0 => p1)
    if (dot(a, b) < -EPS) return 2;
    // 直線上(p0 => p1 => p2)
    if (a.norm() < b.norm()) return -2;
    // 直線上(p0 => p2 => p1)
    return 0;
}