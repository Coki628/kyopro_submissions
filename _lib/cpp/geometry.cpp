/*
・ライブラリ：幾何
*/

#include "_tpl.cpp"


template<typename T>
struct Point {
    T x, y;
    Point () {}
    Point(T x, T y) : x(x), y(y) {}
    Point operator+(const Point &p) { return {x+p.x, y+p.y}; }
    Point operator-(const Point &p) { return {x-p.x, y-p.y}; }
    Point operator*(const Point &p) { return {x*p.x, y*p.y}; }
    Point operator/(const Point &p) { return {x/p.x, y/p.y}; }
    Point operator*(T k) { return {x*k, y*k}; }
    Point operator/(T k) { return {x/k, y/k}; }
    T norm(const Point &p) { return p.x*p.x + p.y*p.y; }
    T abs(const Point &p) { return hypot(x-p.x, y-p.y); }
    T manhattan(const Point &p) { return std::abs(x-p.x) + std::abs(y-p.y); }
};
template<typename T> struct Segment { Point<T> p1, p2; };
#define Line Segment
template<typename T>
struct Circle {
    Point<T> c;
    ld r;
    Circle(Point<T> c, ld r=0.0) : c(c), r(r) {}
};
// 内積
template<typename T> T dot(const Point<T> a, const Point<T> b) { return a.x*b.x + a.y*b.y; }
// 外積
template<typename T> T cross(const Point<T> a, const Point<T> b) { return a.x*b.y - a.y*b.x; }

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
    if (a.norm(a) < b.norm(b)) return -2;
    // 直線上(p0 => p2 => p1)
    return 0;
}

// 回転行列：座標cを軸に座標pから半時計回りにdig度回転させた座標を返す
template<typename T>
Point<T> rotate(Point<T> c, Point<T> p, ld dig) {
    T x = (p.x-c.x)*cos(radians(dig)) - (p.y-c.y)*sin(radians(dig)) + c.x;
    T y = (p.x-c.x)*sin(radians(dig)) + (p.y-c.y)*cos(radians(dig)) + c.y;
    return {x, y};
}

// ∠abcについて、反時計回り側の角度を取得
template<typename T>
ld get_degree(Point<T> a, Point<T> b, Point<T> c) {
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
template<typename T>
pair<T, T> get_a_and_b(Point<T> p1, Point<T> p2) {
    // x座標が同じだと0除算
    assert(p2.x-p1.x != 0);
    T a = (p2.y-p1.y)/(p2.x-p1.x);
    T b = -(p1.x*p2.y/(p2.x-p1.x))+p1.x*p1.y/(p2.x-p1.x)+p1.y;
    return {a, b};
}

// 3次元での2点間距離√((x1-x2)^2+(y1-y2)^2+(z1-z2)^2)
ld dist(tuple<ld, ld, ld> a, tuple<ld, ld, ld> b) {
    return sqrt((get<0>(a)-get<0>(b))*(get<0>(a)-get<0>(b))+(get<1>(a)-get<1>(b))*(get<1>(a)-get<1>(b))+(get<2>(a)-get<2>(b))*(get<2>(a)-get<2>(b)));
}

// アンドリューのアルゴリズム(Monotone Chain)：凸包に使った座標と距離を返す
template<typename T>
vector<pair<Point<T>, ld>> monotone_chain(vector<Point<T>> li) {
    int N = li.size();
    assert(N >= 2);

    sort(ALL(li), [](Point<T> a, Point<T> b) {
        // ソート条件にyも使う
        if (a.x == b.x) return a.y < b.y;
        else return a.x < b.x; 
    });

    // 上半分
    // 使う座標と距離を保持
    vector<pair<Point<T>, ld>> stack;
    stack.pb({li[0], 0});
    stack.pb({li[1], li[0].abs(li[1])});
    rep(i, 2, N) {
        // 1つ前->次 と 1つ前->2つ前 のベクトルで外積をチェックして向きを判定する
        while (stack.size() >= 2 and ccw(stack[stack.size()-2].first, stack[stack.size()-1].first, li[i]) == 1) {
            // 次が反時計回り側にある時は1つ前を外す
            stack.pop_back();
        }
        // 次が時計回り側にあればOKなので進める
        stack.pb({li[i], stack.back().first.abs(li[i])});
    }
    vector<pair<Point<T>, ld>> res;
    rep(i, 1, stack.size()) {
        res.pb(stack[i]);
    }

    // 下半分(やることは同じ)
    stack.clear();
    stack.pb({li[li.size()-1], 0});
    stack.pb({li[li.size()-2], li[li.size()-1].abs(li[li.size()-2])});
    rrep(i, N-3, -1) {
        while (stack.size() >= 2 and ccw(stack[stack.size()-2].first, stack[stack.size()-1].first, li[i]) == 1) {
            stack.pop_back();
        }
        stack.pb({li[i], stack.back().first.abs(li[i])});
    }
    rep(i, 1, stack.size()) {
        res.pb(stack[i]);
    }
    return res;
}

// ピックの定理(多角形の座標から、内部にある格子点の数を出す)
tuple<ll, ll, ll> pick_theorem(vector<Point<ll>> P) {
    ll N = P.size();
    ll S = 0;
    ll b = 0;
    rep(i, N) {
        S += cross(P[i], P[(i+1)%N]);
        auto a = P[i]-P[(i+1)%N];
        b += gcd(abs(a.x), abs(a.y));
    }
    ll i = (abs(S)-b+2)/2;
    // 内部にある格子点の数, 辺上の格子点の数, 面積
    return {i, b, abs(S)};
}
