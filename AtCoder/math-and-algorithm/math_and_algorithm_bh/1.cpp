/*
・きっちり自力AC！
・シグマの式変形、累積和
・iの項を内側シグマの外に出すと掛け算になって、
　内側がjだけになるので、こっちは累積和で解ける。
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
    auto A = LIST(N);

    Accumulate<ll> acc(A);
    ll ans = 0;
    rep(i, N-1) {
        ans += -A[i] * (N-(i+1));
        ans += acc.query(i+1, N);
        // rep(j, i+1, N) {
        //     ans += (A[j]-A[i]);
        // }
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
