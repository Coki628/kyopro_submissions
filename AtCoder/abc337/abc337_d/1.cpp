/*
・きっちり自力AC！
・縦横両方に累積和取った。
　でもこれ2次元累積和ライブラリに突っ込んだらもっと楽できたよね…。
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
    ll H, W, K;
    cin >> H >> W >> K;
    vector<string> grid(H);
    cin >> grid;

    vector<Accumulate<ll>> acc1(H, {W}), acc2(W, {H});
    rep(h, H) {
        rep(w, W) {
            if (grid[h][w] == '.') {
                acc1[h].set(w, 1);
                acc2[w].set(h, 1);
            } else if (grid[h][w] == 'x') {
                acc1[h].set(w, MOD);
                acc2[w].set(h, MOD);
            }
        }
    }
    rep(h, H) {
        acc1[h].build();
    }
    rep(w, W) {
        acc2[w].build();
    }
    ll ans = INF;
    rep(h, H) {
        rep(w, W - K + 1) {
            ll wr = w + K;
            chmin(ans, acc1[h].query(w, wr));
        }
    }
    rep(w, W) {
        rep(h, H - K + 1) {
            ll hr = h + K;
            chmin(ans, acc2[w].query(h, hr));
        }
    }
    if (ans >= MOD) ans = -1;
    print(ans);
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
