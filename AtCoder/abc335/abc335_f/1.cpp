/*
・自力AC。既出パンチ。
・平方分割、MOD累積和、累積和同時進行DP
・yukico1331がほぼ同じで、本番中はそれ少しいじって通した。
　√で分けるのも分かるし、大きい方はいいんだけど、小さい方の遷移が難しい。
　この形の遷移、まだ自力でちゃんと書ける気がしないので要復習だなー。
・ようは「mod aでb」みたいなa,bを状態にして、そこに対する遷移を全部まとめておく。
　自身の確定した値は、各mod(例えば今見ているA[i]が3なら、mod 3で0,1,2のこと)に対して配っておく。
　すると各mod(例えば今欲しい遷移が3の倍数なら、mod 3で0,1,2のこと)で状態がまとまっているので、
　その各modから1回ずつ貰う遷移してくればOKになる。
　何年か後に類題が出た時、この説明で思い出せるかなー。
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
    vector<ll> A(N);
    cin >> A;

    ll D = ceil(sqrt(N));
    // sm[j][k] := mod jでkになるようなマス目に移動する通り数
    auto sm = listnd(D, D, (mint)0);
    // dp[i] := 最後にマスiにいた通り数
    vector<mint> dp(N);
    dp[0] = 1;
    rep(i, N) {
        // 貰う遷移
        rep(j, 1, min(D, i + 1)) {
            dp[i] += sm[j][i % j];
        }
        // 配る遷移
        if (A[i] < D) {
            // 小さいA[i]は累積和への遷移
            sm[A[i]][i % A[i]] += dp[i];
        } else {
            // 大きいA[i]は遷移回数が少ないので直接DPへ遷移
            for (int j = i + A[i]; j < N; j += A[i]) {
                dp[j] += dp[i];
            }
        }
    }
    mint ans = sum(dp);
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
