/*
・自力AC！
・set2つで出し入れした。実装だるめ。。
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
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N, K, Q;
    cin >> N >> K >> Q;

    set<pll> lo, hi;
    vector<ll> A(N);
    rep(i, N - K) {
        lo.insert({A[i], i});
    }
    rep(i, N - K, N) {
        hi.insert({A[i], i});
    }
    ll cur = 0;
    rep(i, Q) {
        ll x, y;
        cin >> x >> y;
        x--;
        if (lo.count({A[x], x})) {
            lo.erase({A[x], x});
            lo.insert({y, x});
        }
        if (hi.count({A[x], x})) {
            hi.erase({A[x], x});
            hi.insert({y, x});
            cur += y - A[x];
        }
        if (lo.size() and (--lo.end())->first > hi.begin()->first) {
            pll a = *hi.begin();
            pll b = *--lo.end();
            cur -= a.first;
            cur += b.first;
            hi.insert(b);
            lo.insert(a);
            hi.erase(a);
            lo.erase(b);
        }
        A[x] = y;
        print(cur);
    }
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
