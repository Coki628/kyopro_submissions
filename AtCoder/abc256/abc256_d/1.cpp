/*
・速攻自力AC。
・RangeSetにありがとうを。
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

#include "segment/RangeSet.hpp"

void solve() {
    ll N;
    cin >> N;

    RangeSet<ll> rs;
    rep(i, N) {
        ll l, r;
        cin >> l >> r;
        rs.insert(l, r-1);
    }

    auto res = rs.get_ranges();
    for (auto& seg : res) {
        seg.second++;
    }
    print(res, '\n');
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
