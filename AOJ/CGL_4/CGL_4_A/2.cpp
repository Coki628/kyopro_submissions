/*
・ライブラリ整備：凸包
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
// #include "template.hpp"
#include "common/print.hpp"

#include "geometry/Point.hpp"
#include "geometry/monotone_chain.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<Point<ll>> P;
    rep(i, N) {
        ll x, y;
        cin >> x >> y;
        P.eb(x, y);
    }
    auto res = monotone_chain(P);
    reverse(ALL(res));
    res.insert(res.begin(), res.back());
    res.pop_back();
    print(res.size());
    for (auto [p, v] : res) {
        print(p);
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
