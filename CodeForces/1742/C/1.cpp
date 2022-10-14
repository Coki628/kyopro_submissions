/*
・自力AC。
・最初Rが横線Bが縦線に限るっての気付かなくて複雑にしてた。。端から端まで塗りきれてる行か列を探す。
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
    ll N = 8;
    vector<string> grid(N);
    rep(i, N) {
        cin >> grid[i];
    }

    rep(i, N) {
        if (grid[i][0] == '.' or grid[i][0] == 'B') continue;
        bool ok = true;
        rep(j, 1, N) {
            if (grid[i][j] != 'R') {
                ok = false;
                break;
            }
        }
        if (ok) {
            print('R');
            return;
        }
    }
    rep(i, N) {
        if (grid[0][i] == '.' or grid[0][i] == 'R') continue;
        bool ok = true;
        rep(j, 1, N) {
            if (grid[j][i] != 'B') {
                ok = false;
                break;
            }
        }
        if (ok) {
            print('B');
            return;
        }
    }
    assert(0);
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
