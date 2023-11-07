/*
・自力AC！
・乗算、素因数
・2,3,5は素数なのでどこかの要素で作ればOK。問題は4。
　これは2*2で2箇所に分けて作れてしまうので、場合分けする。
　偶数が2箇所作れればいいので、偶数の箇所を数える。
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
    vector<ll> A(N);
    cin >> A;

    ll ans = INF;
    if (K == 4) {
        ll evencnt = 0;
        rep(i, N) {
            if (A[i] % 2 == 0) evencnt++;
        }
        chmin(ans, max(2 - evencnt, 0LL));
    }
    rep(i, N) {
        ll cnt = 0;
        while (A[i] % K != 0) {
            A[i]++;
            cnt++;
        }
        chmin(ans, cnt);
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
