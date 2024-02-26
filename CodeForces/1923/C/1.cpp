/*
・きっちり自力AC！
・値が2以上ならどっか上げてどっか下げるみたいにして好きにやれる。
　つまり1が多いとダメ。それを判定するために、累積和を1とその他で分けて持つ。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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

void solve(int testcase) {
    ll N, Q;
    cin >> N >> Q;
    auto A = LIST(N);

    BIT<ll> one(N), others(N);
    rep(i, N) {
        if (A[i] == 1) {
            one.add(i, 1);
        } else {
            others.add(i, A[i]);
        }
    }

    rep(_, Q) {
        ll l, r;
        cin >> l >> r;
        l--;
        ll len = r - l;
        ll onecnt = one.query(l, r);
        ll othercnt = len - onecnt;
        ll othersm = others.query(l, r);
        YESNO(len != 1 and onecnt <= othersm - othercnt);
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    rep(t, T) solve(t);

    return 0;
}
