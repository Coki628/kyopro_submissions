/*
・きっちり自力AC！
・期待値の線形性、主客転倒、二項係数数え上げ
　A[i]*そいつがmaxになれる通り数/全通り みたいなのを二項係数使って求めて全部足す。
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
    ll N, K;
    cin >> N >> K;
    auto A = LIST(N);

    ModTools<mint> mt(N);
    sort(ALL(A));
    mint total = mt.nCr(N, K);
    mint ans = 0;
    rep(i, N) {
        // 自分以外のK-1個を自分より小さいi個から選ぶ通り数
        mint mxcmb = mt.nCr(i, K-1);
        // 自分以外のK-1個を自分より大きいN-i-1個から選ぶ通り数
        mint mncmb = mt.nCr(N-i-1, K-1);
        ans += (mint)A[i] * mxcmb / total;
        ans -= (mint)A[i] * mncmb / total;
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
