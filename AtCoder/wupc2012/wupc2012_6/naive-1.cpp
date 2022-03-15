/*
・これは愚直解を書いたはずが、愚直になっておらず同じやつでWAをする残念なやつ。
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
    auto has = list2d(M, M, false);
    for (auto [x, y] : XY) {
        has[x][y] = true;
    }

    ll ans = 0;
    rep(i, N) {
        auto [x1, y1] = XY[i];
        rep(j, i+1, N) {
            auto [x2, y2] = XY[j];
            if (x1 == x2 or y1 == y2) continue;
            if (not has[x1][y2] or not has[x2][y1]) continue;
            if (x1 > x2) swap(x1, x2);
            if (y1 > y2) swap(y1, y2);
            bool ok = true;
            rep(x, x1+1, x2) {
                rep(y, y1+1, y2) {
                    if (has[x][y]) {
                        ok = false;
                        break;
                    }
                }
                if (not ok) break;
            }
            if (ok) {
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
