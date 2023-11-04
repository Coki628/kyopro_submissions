/*
・きっちり自力AC。
・グリッド、実装
・3*3区画に分けるのだけちょっと考えるけど、
　平方分割のバケットみたいに割り算しながら振り分ければOK。
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
    ll N = 9;
    auto grid = listnd(N, N, 0);
    rep(h, N) {
        rep(w, N) {
            cin >> grid[h][w];
        }
    }

    rep(h, N) {
        set<ll> se;
        rep(w, N) {
            se.insert(grid[h][w]);
        }
        if (se.size() < N) {
            No();
            return;
        }
    }
    rep(w, N) {
        set<ll> se;
        rep(h, N) {
            se.insert(grid[h][w]);
        }
        if (se.size() < N) {
            No();
            return;
        }
    }
    ll M = N / 3;
    auto grid2 = listnd(M, M, set<ll>());
    rep(h, N) {
        rep(w, N) {
            grid2[h / M][w / M].insert(grid[h][w]);
        }
    }
    rep(h, M) {
        rep(w, M) {
            if (grid2[h][w].size() < N) {
                No();
                return;
            }
        }
    }
    Yes();
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
