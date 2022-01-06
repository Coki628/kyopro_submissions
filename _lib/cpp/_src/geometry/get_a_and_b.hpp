#include "../macros.hpp"

// 2点を通る直線の式の係数a,b
template<typename T>
pair<T, T> get_a_and_b(Point<T> p1, Point<T> p2) {
    // x座標が同じだと0除算
    assert(p2.x-p1.x != 0);
    T a = (p2.y-p1.y)/(p2.x-p1.x);
    T b = -(p1.x*p2.y/(p2.x-p1.x))+p1.x*p1.y/(p2.x-p1.x)+p1.y;
    return {a, b};
}
