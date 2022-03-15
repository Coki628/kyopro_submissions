/*
・これはマジの愚直解。
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
            rep(k, j+1, N) {
                auto [x3, y3] = XY[k];
                rep(l, k+1, N) {
                    auto [x4, y4] = XY[l];
                    vector<pll> cur = {{x1, y1}, {x2, y2}, {x3, y3}, {x4, y4}};
                    sort(ALL(cur));
                    auto [x5, y5] = cur[0];
                    auto [x6, y6] = cur[1];
                    auto [x7, y7] = cur[2];
                    auto [x8, y8] = cur[3];
                    if (x5 == x6 and y5 == y7 and x7 == x8 and y6 == y8) {
                        if (x5 == x7 or y6 == y7) continue;
                        bool ok = true;
                        rep(x, x5+1, x7) {
                            rep(y, y5+1, y6) {
                                if (has[x][y]) {
                                    ok = false;
                                    break;
                                }
                            }
                            if (not ok) break;
                        }
                        if (ok) {
                            chmax(ans, (x7-x5)*(y6-y5));
                        }
                    }
                }
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
