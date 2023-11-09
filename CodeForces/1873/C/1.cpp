/*
・自力AC。
・グリッド
・うまいこと添字で整えるか筋肉実装かっていうタイプのやつ。
　前者でやったけど、ちょっと考えたし中々手際よくはいかないねー。
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

void solve() {
    ll H = 10, W = 10;
    vector<string> grid(H);
    cin >> grid;

    // auto test = listnd(H, W, 0);
    ll ans = 0;
    rep(h, H) {
        rep(w, W) {
            ll sub = max({4 - h, h - 5, 4 - w, w - 5});
            // test[h][w] = sub;
            if (grid[h][w] == 'X') {
                ans += 5 - sub;
            }
        }
    }
    // print(test, '\n');
    print(ans);
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
    while (T--) solve();

    return 0;
}
