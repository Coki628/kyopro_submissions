/*
・きっちり自力AC！
・長方形じゃない場所を探す。2*2でL字があるか全チェック。
　これ結構当たり方針だったぽい。(BFSとかDFSした人もいたそうな。)
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

    rep(i, H-1) {
        rep(j, W-1) {
            if (
                grid[i].substr(j, 2) == "01" and grid[i+1].substr(j, 2) == "11" or
                grid[i].substr(j, 2) == "10" and grid[i+1].substr(j, 2) == "11" or
                grid[i].substr(j, 2) == "11" and grid[i+1].substr(j, 2) == "01" or
                grid[i].substr(j, 2) == "11" and grid[i+1].substr(j, 2) == "10"
            ) {
                NO();
                return;
            }
        }
    }
    YES();
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
