/*
・期待値DP、配るDP
・落ち着いて遷移をちゃんと検討すると、配るDPでも通った。
　けど場合分けが増えて考えることが増えてしまう(ソース内コメントも参照)ので、
　やっぱり期待値DPは貰うDP一択にしといた方が無難かも。。
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
    ll N, P;
    cin >> N >> P;

    mint a = (mint)P / 100;
    mint b = (mint)1 - a;
    vector<mint> dp(N + 1);
    rep(i, N, 0, -1) {
        // i=-1への遷移がi=0に入ってはダメ
        if (i >= 2) dp[i - 2] += (dp[i] + 1) * a;
        // i=N-1への遷移はN+1からの遷移というのが無いので、100%をNから遷移させる
        if (i == N) dp[i - 1] += (dp[i] + 1);
        else dp[i - 1] += (dp[i] + 1) * b;
    }
    mint ans = dp[0];
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
