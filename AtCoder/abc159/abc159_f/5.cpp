/*
・dojo set_d_4_4
・自力ならず。。悔しい。
・ナップザック応用
・区間を始める前、途中、後の3状態を持つと、全ての区間について考慮した値が得られる。
　どっかのJOIの問題だかでやったことあるDPだったけど、ここで思い至らなかったなぁ。。
・普通にvectorで3次元組むとAC0.66秒くらいで、ちょっと遅かったので高速化。
　生配列に持ち替えたら0.20秒になった。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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

mint dp[3007][3007][3];

void solve() {
    ll N, S;
    cin >> N >> S;
    auto A = LIST(N);

    // auto dp = list3d<mint>(N+1, S+1, 3, 0);
    dp[0][0][0] = 1;
    rep(i, N) {
        rep(j, S+1) {
            rep(k1, 3) {
                // 前の状態には戻らない
                rep(k2, k1, 3) {
                    dp[i+1][j][k2] += dp[i][j][k1];
                    // この要素を取るなら、右端選択済からは遷移できないし、左端選択前には遷移できない
                    if (j+A[i] <= S and k1 != 2 and k2 != 0) {
                        dp[i+1][j+A[i]][k2] += dp[i][j][k1];
                    }
                }
            }
        }
    }
    mint ans = dp[N][S][2];
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
