/*
・きっちり自力AC！
・グリッドの斜めはx+y,x-yで45度回転にすれば同じ所を集計できる。
　集計後、両斜めの合計から自身のマスの重複を引けばOK。これを全マスで。
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

void solve() {
    ll H, W;
    cin >> H >> W;
    auto grid = listnd(H, W, 0LL);
    rep(h, H) {
        rep(w, W) {
            cin >> grid[h][w];
        }
    }

    map<ll, ll> C1, C2;
    rep(h, H) {
        rep(w, W) {
            C1[h + w] += grid[h][w];
            C2[h - w] += grid[h][w];
        }
    }
    ll ans = 0;
    rep(h, H) {
        rep(w, W) {
            chmax(ans, C1[h + w] + C2[h - w] - grid[h][w]);
        }
    }
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
