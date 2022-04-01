/*
・きっちり自力AC！
・文字列DPする。次回出現indexを前計算で持っとくやつ。
　最初、心のままに貪欲投げたらきっちりWA食らったから頭冷やしてDPしたんだけど、
　やっぱ貪欲でもいけるらしい…。
・「次回出現indexを前計算で持っとくやつ」をライブラリ化した。
　たまに使う時、添字微妙に悩むから。
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

#include "string/get_next_indices.hpp"

void solve() {
    string S;
    cin >> S;
    ll N = S.size();
    vector<int> A(N);
    rep(i, N) {
        A[i] = S[i] - 'a';
    }
    auto nxt = get_next_indices(A, 26);

    // dp[i] := i文字目まで見て、残せた文字数の最大値
    vector<ll> dp(N+1);
    rep(i, N) {
        ll j = nxt[i][A[i]];
        if (j != -1) {
            // この文字を使う(ここと次回出現位置をペアにして残す)
            chmax(dp[j+1], dp[i]+2);
        }
        // この文字を使わない
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
