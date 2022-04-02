/*
・自力AC！
・貪欲
・無駄が出ない範囲で先にクーポン使って、残ったやつソートして、
　大きい方から無駄が出ても残りのクーポン使い切る。で通った。貪欲を信じる気持ち…。
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
    ll N, K, X;
    cin >> N >> K >> X;
    auto A = LIST(N);

    rep(i, N) {
        auto [d, m] = divmod(A[i], X);
        ll use = min(K, d);
        A[i] -= X * use;
        K -= use;
    }
    sort(A.rbegin(), A.rend());
    rep(i, N) {
        ll d = ceil(A[i], X);
        ll use = min(K, d);
        A[i] = max(A[i]-X*use, 0LL);
        K -= use;
    }
    ll ans = sum(A);
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
