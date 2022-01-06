#include "../macros.hpp"

// 座標bを軸にして反時計回りに座標aから座標cに向かう角度を取得
template<typename T>
ld get_degree(Point<T> a, Point<T> b, Point<T> c) {
    // bから見たa,cへ向かうベクトル
    auto v1 = a-b;
    auto v2 = c-b;
    // atan2がx=0から見た角度を返すので、差分を取る
    auto res = degrees(atan2(v2.y, v2.x) - atan2(v1.y, v1.x));
    // 誤差対策のEPS、負の数なら時計回り側にあるので逆向きにする
    if (res < -EPS) res += 360;
    return res;
}
