/*
・公式解より。これくらいなら文字列経由しないでちゃっちゃと割り算できるべきだったね。
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
        auto [hs0, hs1] = divmod(h, 10LL);
        auto [ms0, ms1] = divmod(m, 10LL);
        ll hs = hs0*10 + ms0;
        ll ms = hs1*10 + ms1;
        if (hs <= 23 and ms <= 59) {
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
