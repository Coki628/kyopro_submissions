/*
・自力AC！
・全探索、二分探索
・minを全探索、そのminに対する各A[i]のmaxはにぶたんできる。
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
    auto A = LIST(N);

    ll mn = min(A);
    ll ans = INF;
    rep(x, 1, mn+1) {
        ll mx = x;
        rep(i, N) {
            ll j = bisearch_max(0, K+1, [&](ll p) {
                return A[i]/p >= x;
            });
            chmax(mx, A[i]/j);
        }
        chmin(ans, mx-x);
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
