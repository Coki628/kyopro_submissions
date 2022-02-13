#include "../../combinatorics/ModInt.hpp"
#include "../../combinatorics/ModTools.hpp"
#include "../FormalPowerSeries.hpp"

// nHrの最大までちゃんと作る
ModTools<mint> mt(1e6*2);

// 参考：https://yukicoder.me/submissions/420417
// from baitoさん
// 多項式の冪乗を高速化

// 閉区間 sigma x^(0~r) = (1-x^(r+1)) / (1-x)
// N乗はcombinationで分かる

// 等比数列の和の公式より (0~rは r+1乗になる)
// Σx^(0~r) = (1-x^(r+1)) / (1-x)

// (1-x^r)^nを返す
template<typename T=mint>
FPS<T> pow_term2(int r, int n, int msize) {
    FPS<T> res(msize+1);
    rep(i, n+1) {
        if (i*r <= msize) {
            res[i*r] = mt.nCr(n, i);
            if (i & 1) res[i*r] = -res[i*r];
        }
    }
    return res;
}
// (x^l-x^r)^n
template<typename T=mint>
FPS<T> pow_term2(int l, int r, int n, int msize) {
    FPS<T> res = pow_term2(r-l, n, msize);
    // (x^l)^n * (1-x^(r-l))^n
    assert(l*n < 1e9);
    res = res << l*n;
    if (res.size() > msize+1) res.resize(msize+1);
    return res;
}
// (1-x)^n
template<typename T=mint>
FPS<T> pow_term2(int n, int msize) {
    return pow_term2(1, n, msize);
}
// 1/(1-rx)^nを返す  [x^i]f = nhi * r^i
template<typename T=mint>
FPS<T> pow_term2_inv(int r, int n, int msize) {
    FPS<T> res(msize+1);
    T rb = 1;
    for (int i = 0; i<msize+1; i++) {
        res[i] = mt.nHr(n, i)*rb;
        rb *= r;
    }
    return res;
}
// 1/(1-x)^n
template<typename T=mint>
FPS<T> pow_term2_inv(int n, int msize) {
    return pow_term2_inv(1, n, msize);
}