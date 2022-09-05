/*
・自力AC！
・B[i]=A[i]*(i+1) みたいな配列Bを作っておいて、
　Bの区間和-Aの区間和*i みたいのを全箇所やる。
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
    ll N, M;
    cin >> N >> M;
    auto A = LIST(N);

    auto B = A;
    rep(i, N) {
        B[i] *= i + 1;
    }
    Accumulate<ll> acca(A), accb(B);
    ll ans = -INF;
    rep(i, N-M+1) {
        ll j = i + M;
        ll res = accb.query(i, j) - acca.query(i, j)*i;
        chmax(ans, res);
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
