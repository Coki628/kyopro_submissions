/*
・累積和
・さっきのやつよりはちょい応用だけど、まあこんくらいは、ね。
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
    ll N;
    cin >> N;
    auto A = LIST(N-1);
    ll M;
    cin >> M;
    auto B = LIST(M);
    rep(i, M) B[i]--;

    Accumulate<ll> acc(A);
    ll ans = 0;
    rep(i, M-1) {
        ll l = B[i], r = B[i+1];
        if (l > r) swap(l, r);
        ans += acc.query(l, r);
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
