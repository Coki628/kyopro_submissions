/*
・きっちり自力AC！
・訪問済管理しながら行ける所まで再帰で進んだ。
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

map<char, ll> mp = {
    {'U', 0}, {'D', 1}, {'L', 2}, {'R', 3}
};

void solve() {
    ll H, W;
    cin >> H >> W;
    vector<string> grid(H);
    rep(i, H) cin >> grid[i];

    auto visited = listnd(H, W, false);
    auto rec = [&](auto&& f, ll ch, ll cw) -> void {
        if (visited[ch][cw]) {
            print(-1);
            exit(0);
        }
        visited[ch][cw] = true;
        auto [dh, dw] = dir4[mp[grid[ch][cw]]];
        ll nh = ch + dh;
        ll nw = cw + dw;
        if (nh < 0 or nw < 0 or nh >= H or nw >= W) {
            print(mkp(ch+1, cw+1));
            exit(0);
        }
        f(f, nh, nw);
    };
    rec(rec, 0, 0);
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
