#include "../base.hpp"
#include "../combinatorics/ModTools.hpp"

// 参考：https://ferin-tech.hatenablog.com/entry/2019/08/11/%E3%83%A9%E3%82%B0%E3%83%A9%E3%83%B3%E3%82%B8%E3%83%A5%E8%A3%9C%E9%96%93
// 　　　https://ei1333.github.io/library/math/combinatorics/lagrange-polynomial.cpp
// 使い方
// ・引数：x=0,1,2...の時のyを格納したリスト(N次式なら長さN+1)と、求めたいf(t)のt
// ・戻り値：f(t)の時の値
// ・計算量：O(Nlog(mod)) ※階乗逆元をちゃんと前計算してればO(N)っぽい。

// ラグランジュ補間：値を求める
template<typename T>
T lagrange_polynomial(const vector<T> &y, int64_t t) {
    int N = y.size() - 1;
    ModTools<T> mt(N);
    if(t <= N) return y[t];
    T ret(0);
    vector< T > dp(N + 1, 1), pd(N + 1, 1);
    for(int i = 0; i < N; i++) dp[i + 1] = dp[i] * (t - i);
    for(int i = N; i > 0; i--) pd[i - 1] = pd[i] * (t - i);
    for(int i = 0; i <= N; i++) {
        T tmp = y[i] * dp[i] * pd[i] * mt.factinv[i] * mt.factinv[N-i];
        if((N - i) & 1) ret -= tmp;
        else ret += tmp;
    }
    return ret;
}

// 参考：https://ferin-tech.hatenablog.com/entry/2019/08/11/%E3%83%A9%E3%82%B0%E3%83%A9%E3%83%B3%E3%82%B8%E3%83%A5%E8%A3%9C%E9%96%93
// 　　　https://ei1333.github.io/library/math/combinatorics/lagrange-polynomial-2.cpp
// 使い方
// ・引数：y=f(x)の(x,y)のペアを格納したリストX,Y
// ・戻り値：f(x)=ax^0+bx^1+cx^2+...のa,b,c...を格納したリスト
// ・計算量：O(N^2)

// ラグランジュ補間：係数を求める
template<typename T>
vector<T> lagrange_polynomial(const vector<T> &x, const vector<T> &y) {
    int k = (int) x.size() - 1;

    vector<T> f(k + 1), dp(k + 2);
    dp[0] = 1;
    for(int j = 0; j <= k; j++) {
        for(int l = k + 1; l > 0; l--) {
            dp[l] = dp[l] * -x[j] + dp[l - 1];
        }
        dp[0] *= -x[j];
    }

    for(int i = 0; i <= k; i++) {
        T d = 1;
        for(int j = 0; j <= k; j++) {
            if(i != j) {
                d *= x[i] - x[j];
            }
        }
        T mul = y[i] / d;
        if(x[i] == 0) {
            for(int j = 0; j <= k; j++) {
                f[j] += dp[j + 1] * mul;
            }
        } else {
            T inv = T(1) / (-x[i]), pre = 0;
            for(int j = 0; j <= k; j++) {
                T cur = (dp[j] - pre) * inv;
                f[j] += cur * mul;
                pre = cur;
            }
        }
    }
    return f;
}
