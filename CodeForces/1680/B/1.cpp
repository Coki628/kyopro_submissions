/*
・きっちり自力AC！
・2次元累積和
・自分より左全体と上全体に何もいないかをチェックした。
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

#include "segment/Accumulate2D.hpp"

void solve() {
    ll H, W;
    cin >> H >> W;
    Accumulate2D<ll> acc(H+1, W+1);
    vector<string> grid(H);
    rep(i, H) {
        cin >> grid[i];
        rep(j, W) {
            if (grid[i][j] == 'R') {
                acc.set(i, j, 1);
            }
        }
    }
    acc.build();

    rep(i, H) {
        rep(j, W) {
            if (grid[i][j] == 'R') {
                ll sm1 = acc.query(0, 0, i, W);
                ll sm2 = acc.query(0, 0, H, j);
                if (sm1+sm2 == 0) {
                    YES();
                    return;
                }
            }
        }
    }
    NO();
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
