/*
・きっちり自力AC！
・期待値DP、後ろからDP、遷移高速化
・BITで遷移をまとめる期待値DP。この形は大分慣れてきたかな。
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<mint> A(N);
    cin >> A;

    BIT<mint> dp(N);
    dp.add(N - 1, A[N - 1]);
    rep(i, N - 2, -1, -1) {
        dp.add(i, A[i] + dp.query(i, N) / N);
    }
    mint ans = dp.query(0, N) / N;
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
