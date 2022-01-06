#include "../macros.hpp"
#include "Point.hpp"
#include "cross.hpp"

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
