/*
参考：https://atcoder.jp/contests/abc243/editorial
・自力ならず。
・確率DP、数え上げDP
・結果的には、
　dp[i][j][k] := i種類目まで見て、j個取った状態で、k種類もっている確率
　みたいなDPでi種類目を0~K個取る遷移をするといい。
　i種類目まで見て～、のDPは多少検討したんだけど、このDPに辿り着けなかったな。。
・で、もしこれが分かったとしても各遷移に掛ける値が出なかったと思う。
　(W[i]/total)^l の部分は1回の確率^回数だからまあ分かったかもしれないけど、
　公式解説と実装見ても、階乗で割る意味と、最後に階乗を掛ける意味が分からなかった。
　道場discordで聞いた。この階乗は、K回くじを引いたうち何回目にどれが出たかの考慮だと言う。
　それだと確かに基本的にK!通りあって、i種類目をc個取る時にはc個が重複になるので
　c!で割って減らす、みたいな感じに解釈できそう。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

void solve() {
    ll N, M, K;
    cin >> N >> M >> K;
    auto W = LIST<mint>(N);

    ModTools<mint> mt(max(K, N));
    mint total = sum(W);
    auto dp = list3d<mint>(N+1, K+1, M+1, 0);
    dp[0][0][0] = 1;
    rep(i, N) {
        rep(j, K+1) {
            rep(k, M+1) {
                if (dp[i][j][k] == 0) continue;
                rep(l, K+1) {
                    if (j+l > K or k+(l > 0) > M) break;
                    dp[i+1][j+l][k+(l > 0)] += dp[i][j][k]*(W[i]/total).pow(l)/mt.fact(l);
                }
            }
        }
    }
    mint ans = dp[N][K][M]*mt.fact(K);
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
