/*
・除算の答えが同じものを状態まとめるDP
・たまに見るけど、手際のいいやり方が落とし込めてなかったので復習。
　約数列挙とほぼ同じループをやるけど、
　割り切れないやつを切り捨てた値も使うので貼らないで別途書く。
・後半のDP高速化パートは前計算で累積和やるやつ。
　遷移先も前計算しておいたら大分速くなった。
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
    ll N, K;
    cin >> N >> K;

    vector<ll> A;
    // 約数列挙と似てるけどこれは割り切れないやつも集める
    for (ll i = 1; i * i <= N; i++) {
        A.eb(i);
        A.eb(N / i);
    }
    UNIQUE(A);
    ll M = A.size();
    // 遷移先の前計算(内側で直接やっても通ったけど)
    vector<ll> X(M);
    rep(j, M) {
        X[j] = bisearch_max(-1, M, [&](ll x) {
            return A[j] * A[x] <= N;
        });
    }
    vector<ll> W(M);
    W[0] = 1;
    rep(i, 1, M) {
        W[i] = A[i] - A[i - 1];
    }
    auto dp = listnd(K, M, (mint)0);
    rep(j, M) {
        dp[0][j] = W[j];
    }
    rep(i, 1, K) {
        Accumulate<mint> acc(dp[i - 1]);
        rep(j, M) {
            // rep(k, M) {
            //     if (A[j] * A[k] <= N) {
            //         dp[i][j] += dp[i - 1][k] * W[j];
            //     }
            // }
            // ll x = bisearch_max(-1, M, [&](ll x) {
            //     return A[j] * A[x] <= N;
            // });
            // rep(k, x + 1) {
            //     dp[i][j] += dp[i - 1][k] * W[j];
            // }
            dp[i][j] += acc.query(0, X[j] + 1) * W[j];
        }
    }
    mint ans = sum(dp[K - 1]);
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
