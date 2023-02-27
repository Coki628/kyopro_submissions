/*
・きっちり自力AC！
・setで訪問済み管理。
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
    ll N;
    cin >> N;
    string S;
    cin >> S;

    string D = "LRDU";
    map<char, ll> mp;
    rep(i, 4) {
        mp[D[i]] = i;
    }
    set<pll> visited;
    int cx = 0, cy = 0;
    visited.insert({cx, cy});
    rep(i, N) {
        auto [dx, dy] = dir4[mp[S[i]]];
        cx += dx, cy += dy;
        if (visited.count({cx, cy})) {
            Yes();
            return;
        }
        visited.insert({cx, cy});
    }
    No();
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
