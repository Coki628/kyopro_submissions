/*
・これは部分点2
・縦横両方の区切り位置をビット全探索する。
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
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll H, W;
    cin >> H >> W;
    auto grid = list2d(H, W, 0);
    rep(i, H) {
        rep(j, W) {
            cin >> grid[i][j];
        }
    }

    assert(H <= 6 and W <= 6);

    ll ans = 0;
    rep(bit1, 1<<(H-1)) {
        rep(bit2, 1<<(W-1)) {
            if (bit1 == 0 and bit2 == 0) continue;
            ll n = popcount(bit1)+1;
            ll m = popcount(bit2)+1;
            auto C = list2d(n, m, 0);
            ll i = 0;
            rep(h, H) {
                ll j = 0;
                rep(w, W) {
                    C[i][j] += grid[h][w];
                    if (bit2>>w & 1) {
                        j++;
                    }
                }
                if (bit1>>h & 1) {
                    i++;
                }
            }
            vector<ll> V;
            rep(i, n) {
                rep(j, m) {
                    V.eb(C[i][j]);
                }
            }
            UNIQUE(V);
            if (V.size() == 1) {
                ans++;
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
