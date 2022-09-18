/*
・先頭と末尾の#。前からと後ろからでチェック。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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
    ll N = 10;
    vector<string> grid(N);
    rep(i, N) cin >> grid[i];

    ll a, b, c, d;
    bool ok = false;
    rep(i, N) {
        rep(j, N) {
            if (grid[i][j] == '#') {
                a = i + 1;
                c = j + 1;
                ok = true;
                break;
            }
        }
        if (ok) break;
    }
    ok = false;
    rep(i, N-1, -1, -1) {
        rep(j, N-1, -1, -1) {
            if (grid[i][j] == '#') {
                b = i + 1;
                d = j + 1;
                ok = true;
                break;
            }
        }
        if (ok) break;
    }
    print(mkp(a, b));
    print(mkp(c, d));
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
