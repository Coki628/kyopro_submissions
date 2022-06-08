/*
・さくっと自力AC！
・本日の癒し枠。S[i]='B'の所1にした累積和取って、区間長K全部見てK-区間和の最小。
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
    ll N, K;
    cin >> N >> K;
    string S;
    cin >> S;

    Accumulate<ll> acc(N);
    rep(i, N) {
        if (S[i] == 'B') {
            acc.set(i, 1);
        }
    }
    acc.build();

    ll ans = INF;
    rep(i, N-K+1) {
        ll j = i + K;
        chmin(ans, K-acc.query(i, j));
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
