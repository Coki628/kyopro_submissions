/*
・きっちり自力AC！
・今日はここまで速くていい感じだった。
・累積和してDP
・白い部分を隠せる最大値、みたいなDPして合計から引いた。
　重なって得することは基本的にはないので、最後以外は重ねず進める。
　これで遷移はその位置から敷くか敷かないかだけなので、
　後は位置と敷いた個数持った2乗DPでOK。
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

class Solution {
public:
    int minimumWhiteTiles(string S, int M, int L) {
        ll N = S.size();

        Accumulate<ll> acc(N);
        ll total = 0;
        rep(i, N) {
            if (S[i] == '1') {
                acc.set(i, 1);
                total++;
            }
        }
        acc.build();

        auto dp = list2d(N+1, M+1, 0LL);
        rep(i, N) {
            rep(j, M+1) {
                chmax(dp[i+1][j], dp[i][j]);
                if (j+1 <= M) {
                    chmax(dp[min(i+L, N)][j+1], dp[i][j] + acc.query(i, min(i+L, N)));
                }
            }
        }
        ll ans = total - max(dp[N]);
        return ans;
    }
};

#ifdef __LOCAL
    int main() {
        // Solution sol;
        // auto res = sol.funcName();
        // print(res);
        return 0;
    }
#endif
