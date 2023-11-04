/*
・きっちり自力AC！
・Mo、座圧BIT
・これはMoに乗る。以下、伸び縮み時の更新処理について。
　同値でも順序があって欲しかったので、ペアで座圧するやつにした。
　いずれにしろ、√の内側は極力軽くしたいので、
　先に元の列もlogかけて圧縮しておいて、処理内はO(1)で復元する。
・最初普通出したら1.78秒くらいで、TL5秒だからまあいいんだけど、
　BITにぶたんのlog1個にするやつを重い腰上げて作った。
　そしたら0.91秒とかになったので、かなり効果はあった。
　ただでさえ速いBITがにぶたんのlog1個にできたのはかなり頼もしい。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
// #define CAST_MINT_TO_LL
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

#include "datastructure/Mo.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    Compress<pll> cp;
    rep(i, N) {
        cp.add({A[i], i});
    }
    cp.build();
    vector<ll> cpa;
    rep(i, N) {
        cpa.eb(cp[{A[i], i}]);
    }
    Mo mo(N);
    ll Q;
    cin >> Q;
    rep(i, Q) {
        ll l, r;
        cin >> l >> r;
        l--;
        mo.add(l, r);
    }
    BIT<int> bit(N);
    ll cur = 0;
    auto add = [&](int i) -> void {
        int m = cpa[i];
        int l = bit.bisearch_back(0, m - 1, 1);
        int r = bit.bisearch_fore(m + 1, N - 1, 1);
        if (l != -1 and r != -1) {
            cur -= pow(cp.unzip(r).first - cp.unzip(l).first, 2);
        }
        if (l != -1) {
            cur += pow(cp.unzip(m).first - cp.unzip(l).first, 2);
        }
        if (r != -1) {
            cur += pow(cp.unzip(r).first - cp.unzip(m).first, 2);
        }
        bit.add(m, 1);
    };
    auto erase = [&](int i) -> void {
        int m = cpa[i];
        int l = bit.bisearch_back(0, m - 1, 1);
        int r = bit.bisearch_fore(m + 1, N - 1, 1);
        if (l != -1) {
            cur -= pow(cp.unzip(m).first - cp.unzip(l).first, 2);
        }
        if (r != -1) {
            cur -= pow(cp.unzip(r).first - cp.unzip(m).first, 2);
        }
        if (l != -1 and r != -1) {
            cur += pow(cp.unzip(r).first - cp.unzip(l).first, 2);
        }
        bit.add(m, -1);
    };
    vector<ll> ans(Q);
    auto out = [&](int i) -> void {
        ans[i] = cur;
    };
    mo.build(add, erase, out);
    print(ans, '\n');
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}
