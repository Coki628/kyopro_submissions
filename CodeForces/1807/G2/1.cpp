/*
・自力ならず。
・部分和DP、bitset高速化、QCFium法
・部分和DPの高速化でbitset全く思い出せなかったのは良くなかったな…。
　20万の2乗で明らかに厳しそうだが、なんとかなる。
　実際普通にやると無理で、QCFium入れたら通った。
　あと、C++17でやると1.80秒くらいでギリなのに、提出C++20で同じコード投げると0.90秒まで速くなった。
・bitsetで上位側にはみ出したビット無視していいのか分からなかったけど、
　無視しちゃっていいみたいだった。なので実装はとても簡潔。
・ちなみにこれはやっぱり想定解じゃないらしく、賢い貪欲がある。
　ソートして累積していくと、その手前までの累積和以下は全て作れるそう。まじかよ…。
*/

#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

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

bitset<200001> dp;

void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    cin >> A;

    sort(ALL(A));
    if (A[0] != 1) {
        NO();
        return;
    }
    dp = {};
    dp[0] = 1;
    rep(i, N - 1) {
        dp |= dp << A[i];
        if (not dp[A[i + 1]]) {
            NO();
            return;
        }
    }
    YES();
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
