/*
・きっちり自力AC！
・Nが10しかないので遷移先は少なく、普通にDPできる。
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
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;
    ll M;
    cin >> M;
    vector<ll> B(M);
    cin >> B;
    ll X;
    cin >> X;

    vector<ll> ng(X + 1);
    rep(i, M) {
        ng[B[i]] = 1;
    }
    vector<ll> dp(X + 1);
    dp[0] = 1;
    rep(i, X) {
        if (ng[i] or not dp[i]) continue;
        rep(j, N) {
            if (i + A[j] <= X and not ng[i + A[j]]) {
                dp[i + A[j]] = 1;
            }
        }
    }
    if (dp[X]) {
        Yes();
    } else {
        No();
    }
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
