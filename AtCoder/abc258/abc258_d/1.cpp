/*
・自力AC！
・A+Bの累積和とBの累積min持ちながら、そこまでクリアして残り最小値で全部みたいのを全探索。
　INFが足りないのに結構気付けなくて焦った…。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
// #define CAST_MINT_TO_LL
#include "base.hpp"

// constexpr long long INF = 1e18;
constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N, X;
    cin >> N >> X;
    vector<ll> A(N), B(N), AB(N);
    rep(i, N) {
        cin >> A[i] >> B[i];
        AB[i] = A[i] + B[i];
    }

    Accumulate<ll> acc(AB);
    ll mn = INF, ans = INF;
    rep(i, N) {
        chmin(mn, B[i]);
        if (X-(i+1) >= 0) {
            chmin(ans, acc.query(0, i+1) + mn*(X-(i+1)));
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
