/*
・きっちり自力AC！
・フィボナッチ作ってシミュして端数整えればOK。
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

const ll MX = 679891637638612258;

void solve() {
    ll n;
    cin >> n;

    vector<ll> dp = {1, 2};
    while (1) {
        ll p = dp[dp.size() - 1];
        ll pp = dp[dp.size() - 2];
        dp.eb(p + pp);
        if (dp.back() >= MX) break;
    }
    ll M = dp.size();

    ll x = 0, y = 1;
    rep(i, 1, M) {
        ll diff = dp[i] - dp[i - 1];
        if (n <= dp[i]) {
            ll rest = n - dp[i - 1];
            x += rest * pow(-1, i);
            break;
        }
        x += diff * pow(-1, i);
    }
    print(x);
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
