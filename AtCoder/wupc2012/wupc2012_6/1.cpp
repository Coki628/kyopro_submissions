/*
・dojo set_e_5_f
・なんとか自力AC！
・2次元累積和
・Gを先にやってしまったので終了後AC。
　2次元累積和をいつもより一回り小さくするだけなのに、何か色々バグり散らかして大変だった。。
・結局最終的にWAだったのは、内側ループの外で auto [x1, y1] = XY[i] ってしたやつを
　内側ループの中で swap(x1, x2) とかしちゃってるから値変わっておかしくなってたのが原因。
　これ絶対しょうもねぇやつだろなって思いながらデバッグしてたけど、まじでしょうもねぇ…。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<pll> XY;
    rep(i, N) {
        ll x, y;
        cin >> x >> y;
        XY.eb(x, y);
    }

    const ll M = 1000;
    auto acc = list2d(M, M, 0LL);
    auto has = list2d(M, M, false);
    for (auto [x, y] : XY) {
        acc[x][y]++;
        has[x][y] = true;
    }
    rep(i, M) {
        rep(j, M-1) {
            acc[i][j+1] += acc[i][j];
        }
    }
    rep(j, M) {
        rep(i, M-1) {
            acc[i+1][j] += acc[i][j];
        }
    }

    ll ans = 0;
    rep(i, N) {
        rep(j, i+1, N) {
            auto [x1, y1] = XY[i];
            auto [x2, y2] = XY[j];
            if (x1 == x2 or y1 == y2) continue;
            if (not has[x1][y2] or not has[x2][y1]) continue;
            if (x1 > x2) swap(x1, x2);
            if (y1 > y2) swap(y1, y2);
            ll sm = acc[x1][y1]-acc[x1][y2-1]-acc[x2-1][y1]+acc[x2-1][y2-1];
            if (sm == 0) {
                chmax(ans, (x2-x1)*(y2-y1));
            }
        }
    }
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
