/*
・きっちり自力AC！
・累積和にぶたんでS個になる最長まで右端伸ばす。
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
    ll N, S;
    cin >> N >> S;
    auto A = LIST(N);

    Accumulate<ll> acc(A);
    ll ans = INF;
    rep(i, N) {
        ll j = acc.bisearch_fore(i, N-1, S+1);
        if (j == -1) {
            if (acc.query(i, N) == S) {
                chmin(ans, N - (N-i));
            }
        } else {
            if (acc.query(i, j) == S) {
                chmin(ans, N - (j-i));
            }
        }
    }
    if (ans == INF) ans = -1;
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
