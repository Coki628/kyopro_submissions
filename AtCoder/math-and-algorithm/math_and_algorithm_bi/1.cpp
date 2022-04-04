/*
・きっちり自力AC！
・二項係数、寄与、足し算ピラミッド
・なんかパスカルみたいなやつ。経路問題に帰着できて二項係数になるやつ。
　それぞれの位置にある値が使われる回数は、
　終点に至るまでの経路数で表せるので、二項係数と掛け合わせればOK。
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

    ModTools<mint> mt(N);
    mint ans = 0;
    rep(i, N) {
        ans += mt.nCr(N-1, i) * A[i];
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
