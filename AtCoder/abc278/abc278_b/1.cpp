/*
・時刻管理系
・PASTに出そう。数値と文字列行ったり来たりして判定頑張る。
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
    ll h, m;
    cin >> h >> m;

    while (1) {
        string hs = zfill(tostr(h), 2);
        string ms = zfill(tostr(m), 2);
        string hs2 = {hs[0], ms[0]};
        string ms2 = {hs[1], ms[1]};
        if (toint(hs2) <= 23 and toint(ms2) <= 59) {
            print(mkp(h, m));
            return;
        }
        m = (m+1) % 60;
        if (m == 0) {
            h = (h+1) % 24;
        }
    }
    assert(0);
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
