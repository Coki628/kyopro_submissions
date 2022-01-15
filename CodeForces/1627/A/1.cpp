/*
・きっちり自力AC！
・グリッド上に黒マスが1つでもあるか、目的のマスと同じ行か列にあるか、
　目的のマスが黒マスか、で場合分け。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

void solve() {
    ll H, W, sh, sw;
    cin >> H >> W >> sh >> sw;
    sh--; sw--;
    vector<string> grid(H);
    rep(i, H) {
        cin >> grid[i];
    }

    bool ok = false;
    rep(i, H) {
        rep(j, W) {
            if (grid[i][j] == 'B') {
                ok = true;
                break;
            }
        }
        if (ok) break;
    }
    if (not ok) {
        print(-1);
        return;
    }

    ll ans = 2;
    ok = false;
    rep(i, H) {
        if (grid[i][sw] == 'B') {
            ok = true;
            break;
        }
    }
    rep(j, W) {
        if (grid[sh][j] == 'B') {
            ok = true;
            break;
        }
    }
    if (ok) ans--;
    if (grid[sh][sw] == 'B') {
        ans--;
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
