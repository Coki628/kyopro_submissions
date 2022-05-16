/*
参考：https://ark4rk.hatenablog.com/entry/2018/01/08/002508
・自力ならず。。
・最大部分配列問題、連続部分列のDP
・前提として、文字種の全ペアを(最小出現数, 最大出現数)として全探索する。
　そもそもこれが出なかったからね…。で、そしたら各ペアは、-1,+1に変換した列で、
　最大部分配列問題ってのをやることになる。ようは連続部分列の値の最大化。
　調べてたら分割統治法が紹介されていたので、とりあえずやってみる。
・なんかTLでsiさんがlog付きでTLEになるって言ってたのはこれのことか…。
・公式はKadane's algorithmっていうのを紹介してたけど、
　今回は「ある文字を1回でも使ったか」を状態に持たないといけないので、
　結局そのまま適用できなくてアドホックっぽい感じになっちゃう。
・よくよく考えると、連続部分列で(開始前,継続中,終了後)の3状態を持つDPが、
　今回のやつに適用できそうだと気付く。これだと追加の状態も容易に持てる。
　実際合ってるっぽいんだけど、なんかTLEする。
　26*26*10000=676万で、これに定数添字乗るくらいでC++がTLEするとは思えないんだけどね…。
・限界高速化したら通った。なんか細かいループとかが(多分りとこ環境だと)地味に重いみたい。
　定数のループ全部ベタ書きにしたら1.90秒くらいで通った。かかりすぎだろ…。
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
using mint = ModInt<MOD>;
#include "template.hpp"

int dp[2][3][2];

class Solution {
public:
    int largestVariance(string S) {
        ll N = S.size();
        vector<int> A(N);
        rep(i, N) {
            A[i] = S[i] - 'a';
        }
        ll M = 26;
        int ans = 0;
        rep(c1, M) {
            rep(c2, M) {
                if (c1 == c2) continue;
                dp[0][0][1] = -MOD;
                dp[0][1][0] = -MOD;
                dp[0][1][1] = -MOD;
                dp[0][2][0] = -MOD;
                dp[0][2][1] = -MOD;
                dp[1][0][0] = -MOD;
                dp[1][0][1] = -MOD;
                dp[1][1][0] = -MOD;
                dp[1][1][1] = -MOD;
                dp[1][2][0] = -MOD;
                dp[1][2][1] = -MOD;
                dp[0][0][0] = 0;
                rep(i, N) {
                    int cur = A[i] == c1 ? -1 : A[i] == c2 ? 1 : 0;
                    chmax(dp[(i+1)%2][0][0], dp[i%2][0][0]);
                    chmax(dp[(i+1)%2][2][0], dp[i%2][1][0]);
                    chmax(dp[(i+1)%2][2][1], dp[i%2][1][1]);
                    chmax(dp[(i+1)%2][2][0], dp[i%2][2][0]);
                    chmax(dp[(i+1)%2][2][1], dp[i%2][2][1]);
                    chmax(dp[(i+1)%2][1][(cur == -1)], dp[i%2][0][0]+cur);
                    chmax(dp[(i+1)%2][1][(cur == -1)], dp[i%2][1][0]+cur);
                    chmax(dp[(i+1)%2][1][1], dp[i%2][1][1]+cur);
                    dp[i%2][0][0] = -MOD;
                    dp[i%2][0][1] = -MOD;
                    dp[i%2][1][0] = -MOD;
                    dp[i%2][1][1] = -MOD;
                    dp[i%2][2][0] = -MOD;
                    dp[i%2][2][1] = -MOD;
                }
                chmax(ans, max(dp[N%2][1][1], dp[N%2][2][1]));
            }
        }
        return ans;
    }
};

#ifdef __LOCAL
    int main() {
        Solution sol;
        auto res = sol.largestVariance("aababbb");
        print(res);
        return 0;
    }
#endif
