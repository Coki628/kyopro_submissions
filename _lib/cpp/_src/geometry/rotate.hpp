#include "../macros.hpp"
#include "Point.hpp"

// 回転行列：座標cを軸に座標pから半時計回りにdig度回転させた座標を返す
template<typename T>
Point<T> rotate(Point<T> c, Point<T> p, ld dig) {
    T x = (p.x-c.x)*cos(radians(dig)) - (p.y-c.y)*sin(radians(dig)) + c.x;
    T y = (p.x-c.x)*sin(radians(dig)) + (p.y-c.y)*cos(radians(dig)) + c.y;
    return {x, y};
}
