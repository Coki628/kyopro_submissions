/*
・きっちり自力AC！
・右下から黒くできるとこやってく。grid[0][0]が黒なら即NG。
　それ以外の左端は上と一緒にやればいい。
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
    ll H, W;
    cin >> H >> W;
    vector<string> grid(H);
    rep(i, H) cin >> grid[i];

    if (grid[0][0] == '1') {
        print(-1);
        return;
    }

    vector<string> cur(H, string(W, '0'));
    vector<array<ll, 4>> ans;
    rep(i, H-1, -1, -1) {
        rep(j, W-2, -1, -1) {
            if (grid[i].substr(j, 2) == "01" or grid[i].substr(j, 2) == "11") {
                ans.pb({i+1, j+1, i+1, j+2});
                cur[i][j] = '0';
                cur[i][j+1] = '1';
            }
        }
        if (grid[i][0] == '1') {
            ans.pb({i, 1, i+1, 1});
            cur[i][0] = '1';
            cur[i-1][0] = '0';
        }
    }
    assert(cur == grid);

    print(ans.size());
    rep(i, ans.size()) {
        print(ans[i]);
    }
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
