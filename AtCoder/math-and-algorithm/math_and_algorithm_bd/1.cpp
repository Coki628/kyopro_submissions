/*
・なんとか自力AC
・余事象
・最初Kの制約が小さいのに気づいてなくて、大変なやつ書いてた…。
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
#include "template.hpp"

void solve() {
    ll N, K;
    cin >> N >> K;

    auto count = [&](ll a, ll b) -> ll {
        ll l = max({a-K+1, b-K+1, 1LL});
        ll r = min({a+K-1, b+K-1, N});
        ll res = max(r-l+1, 0LL);
        return res;
    };

    ll cnt = 0;
    rep(a, 1, N+1) {
        rep(b, max(a-K+1, 1LL), min(a+K, N+1)) {
            cnt += count(a, b);
        }
    }
    ll ans = pow(N, 3) - cnt;
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
