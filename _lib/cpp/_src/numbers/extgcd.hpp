#pragma once

// 拡張ユークリッドの互除法(ax+by=gcd(a, b)の解を求める)
template<typename T>
T extgcd(T a, T b, T& x, T& y) {
    T d = a;
    if (b != 0) {
        d = extgcd(b, a%b, y, x);
        y -= (a/b) * x;
    } else {
        x = 1; y = 0;
    }
    return d;
}
