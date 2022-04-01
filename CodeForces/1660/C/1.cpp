/*
・きっちり自力AC！
・文字列DPする。次回出現indexを前計算で持っとくやつ。
　最初、心のままに貪欲投げたらきっちりWA食らったから頭冷やしてDPしたんだけど、
　やっぱ貪欲でもいけるらしい…。
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
    string S;
    cin >> S;
    ll N = S.size();
    vector<ll> A(N);
    rep(i, N) {
        A[i] = S[i] - 'a';
    }

    ll M = 26;
    auto nxt = list2d(N+1, M, -1);
    rep(i, N-1, -1, -1) {
        rep(j, M) {
            if (j == A[i]) {
                nxt[i][j] = i;
            } else {
                nxt[i][j] = nxt[i+1][j];
            }
        }
    }

    vector<ll> dp(N+1);
    rep(i, N) {
        ll j = nxt[i+1][A[i]];
        if (j != -1) {
            chmax(dp[j+1], dp[i]+2);
        }
        chmax(dp[i+1], dp[i]);
    }
    ll ans = N - dp[N];
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
