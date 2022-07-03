/*
・Bにしては結構大変。
　8方向・始点・N回みたいなループで全探索。負数のmod取りもちゃんとやる。
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

#include "grid/constants/dir8.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<string> grid(N);
    rep(i, N) {
        cin >> grid[i];
    }

    string ans;
    for (auto [dh, dw] : dir8) {
        rep(sh, N) {
            rep(sw, N) {
                ll ch = sh, cw = sw;
                string S;
                rep(_, N) {
                    S.pb(grid[ch][cw]);
                    ch = modulo(ch+dh, N), cw = modulo(cw+dw, N);
                }
                chmax(ans, S);
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
