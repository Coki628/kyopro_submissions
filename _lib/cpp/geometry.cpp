/*
・ライブラリ：幾何
*/

#include "_tpl.cpp"


struct Point {
    ld x, y;
    Point operator+(const Point &p) { return {x+p.x, y+p.y}; }
    Point operator-(const Point &p) { return {x-p.x, y-p.y}; }
    Point operator*(const Point &p) { return {x*p.x, y*p.y}; }
    Point operator/(const Point &p) { return {x/p.x, y/p.y}; }
    Point operator*(ld k) { return {x*k, y*k}; }
    Point operator/(ld k) { return {x/k, y/k}; }
    ld norm(const Point &p) { return p.x*p.x + p.y*p.y; }
    ld abs(const Point &p) { return hypot(x-p.x, y-p.y); }
};
struct Segment { Point p1, p2; };
using Line = Segment;
struct Circle {
    Point c;
    ld r;
    Circle(Point c=Point(), ld r=0.0) : c(c), r(r) {}
};
// 内積
ld dot(const Point a, const Point b) { return a.x*b.x + a.y*b.y; }
// 外積
ld cross(const Point a, const Point b) { return a.x*b.y - a.y*b.x; }

// 回転行列：座標cを軸に座標pから半時計回りにdig度回転させた座標を返す
Point rotate(Point c, Point p, ld dig) {
    ld x = (p.x-c.x)*cos(radians(dig)) - (p.y-c.y)*sin(radians(dig)) + c.x;
    ld y = (p.x-c.x)*sin(radians(dig)) + (p.y-c.y)*cos(radians(dig)) + c.y;
    return {x, y};
}

// ∠abcについて、反時計回り側の角度を取得
ld get_degree(Point a, Point b, Point c) {
    // bから見たa,cへ向かうベクトル
    auto v1 = a-b;
    auto v2 = c-b;
    // atan2がx=0から見た角度を返すので、差分を取る
    auto res = degrees(atan2(v2.y, v2.x) - atan2(v1.y, v1.x));
    // 誤差対策のEPS、負の数なら時計回り側にあるので逆向きにする
    if (res < 0-EPS) res += 360;
    return res;
}

// 余弦定理(辺a,bと間の角度degから、反対側の辺cを求める)
ld cos_formula(ld a, ld b, ld deg) {
    return sqrt(a*a+b*b-2*a*b*cos(radians(deg)));
}

// 2点を通る直線の式の係数a,b
pair<ld, ld> get_a_and_b(Point p1, Point p2) {
    // x座標が同じだと0除算
    assert(p2.x-p1.x != 0);
    ld a = (p2.y-p1.y)/(p2.x-p1.x);
    ld b = -(p1.x*p2.y/(p2.x-p1.x))+p1.x*p1.y/(p2.x-p1.x)+p1.y;
    return {a, b};
}

// 3次元での2点間距離√((x1-x2)^2+(y1-y2)^2+(z1-z2)^2)
ld dist(tuple<ld, ld, ld> a, tuple<ld, ld, ld> b) {
    return sqrt((get<0>(a)-get<0>(b))*(get<0>(a)-get<0>(b))+(get<1>(a)-get<1>(b))*(get<1>(a)-get<1>(b))+(get<2>(a)-get<2>(b))*(get<2>(a)-get<2>(b)));
}
